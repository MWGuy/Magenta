#include "ValueAnimation.h"
#include <thread>

#ifdef _WIN32
#include <windows.h>
#endif

namespace Magenta
{
	void AnimatedValue::setValue(ValueAnimation* animation)
	{
		long relativePosition = animation->position - duration;
		if (relativePosition < 0)
			*value = startValue;
		if (relativePosition > duration)
			*value = endValue;
		*value = (endValue - startValue) / duration * relativePosition + startValue;
	}

	AnimatedValue::AnimatedValue(TargetValue target, double startVal, double endVal,
		Seconds durationS, Seconds originS)
		: origin(originS), duration(durationS), startValue(startVal), endValue(endVal), value(target)
	{
	}

	void ValueAnimation::nextFrame()
	{
		if (isPaused())
			return;

		if (direction == AnimationDirection::Forward
			|| direction == AnimationDirection::ForwardReverse)
		{
			position += 0.001 * speed;
			if (position > duration)
			{
				if(direction == AnimationDirection::ForwardReverse)
					direction = BackwardReverse;
				else
					toStart();
			}
		} else
		{
			position -= 0.001 * speed;
			if (position < 0)
			{
				if (direction == AnimationDirection::BackwardReverse)
					direction = ForwardReverse;
				else
					toEnd();
			}
		}
		for (size_t i = 0; i < values.size(); i++)
			values[i].setValue(this);

		if (layoutToUpdate != 0)
			layoutToUpdate->update();
	}

	bool ValueAnimation::isPaused() const {
		return mPaused;
	}

	void ValueAnimation::append(AnimatedValue value) {
		values.push_back(value);
		values.back().setValue(this);
	}

	void ValueAnimation::toStart() {
		position = 0;
	}

	void ValueAnimation::toBeginning() {
		if (direction == AnimationDirection::Forward
			|| direction == AnimationDirection::ForwardReverse)
		{
			toStart();
		}
		else toEnd();
	}

	void ValueAnimation::toEnd() {
		position = duration - 1;
	}

	void ValueAnimation::play() {
		mPaused = false;
	}

	void ValueAnimation::playFromBeginning() {
		toBeginning();
		play();
	}

	void ValueAnimation::pause() {
		mPaused = true;
	}

	void ValueAnimation::stop() {
		pause();
		toBeginning();
	}

	void ThreadCircle(ValueAnimation* animation)
	{
		while (animation->timerState == Working)
		{
			for (size_t i = 0; i < animation->values.size(); i++)
				animation->values[i].setValue(animation);
#ifdef _WIN32 
			Sleep(VALUE_ANIMATION_FREQURENCY);
#endif
		}
		animation->timerState = Terminated;
	}

	ValueAnimation::ValueAnimation(Seconds durationS, Layout* optional)
		: mPaused(false), timerState(Working), duration(durationS), position(0), direction(AnimationDirection::Forward),
		repeat(false), speed(1.0f), layoutToUpdate(optional)
	{
		timerThr = std::thread(ThreadCircle, this);
		timerThr.detach();
	}

	ValueAnimation::~ValueAnimation()
	{
		timerState = PendingToTerminate;
		while (timerState != Terminated)
		{ // Wait for safe thread stopping
		}
	}
}
