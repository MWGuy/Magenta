#include "ValueAnimation.h"
#include "Window.h"
#include "Layout.h"
#include <future>

namespace Magenta
{
	void AnimatedValue::setValue(ValueAnimation_* animation)
	{
		double relativePosition = animation->position - origin;
		if (relativePosition < 0) {
			value = startValue;
			return;
		}
		if (relativePosition > duration) {
			value = endValue;
			return;
		}
		value = (endValue - startValue) / duration * relativePosition + startValue;
	}

	AnimatedValue::AnimatedValue(TargetValue target, double startVal, double endVal,
		Seconds durationS, Seconds originS)
		: origin(originS), duration(durationS), startValue(startVal), endValue(endVal), value(target)
	{
	}

	void ValueAnimation_::nextFrame()
	{
		if (isPaused())
			return;

		if (direction == AnimationDirection::Forward
			|| direction == AnimationDirection::ForwardReverse)
		{
			position += 0.01 * speed;
			if (position > duration)
			{
				if (repeat)
				{
					if (direction == AnimationDirection::ForwardReverse)
						direction = BackwardReverse;
					else
						toStart();
				}
				else stop();
			}
		} else
		{
			position -= 0.01 * speed;
			if (position < 0)
			{
				if (repeat)
				{
					if (direction == AnimationDirection::BackwardReverse)
						direction = ForwardReverse;
					else
						toEnd();
				}
				else stop();
			}
		}
		for (size_t i = 0; i < values.size(); i++)
			values[i].setValue(this);
	}

	bool ValueAnimation_::isPaused() const {
		return mPaused;
	}

	void ValueAnimation_::append(AnimatedValue value) {
		values.push_back(value);
		values.back().setValue(this);
	}

	void ValueAnimation_::toStart() {
		position = 0;
	}

	void ValueAnimation_::toBeginning() {
		if (direction == AnimationDirection::Forward
			|| direction == AnimationDirection::ForwardReverse)
		{
			toStart();
		}
		else toEnd();
	}

	void ValueAnimation_::toEnd() {
		position = duration - 1;
	}

	void ValueAnimation_::play() {
		mPaused = false;
	}

	void ValueAnimation_::playFromBeginning() {
		toBeginning();
		play();
	}

	void ValueAnimation_::pause() {
		mPaused = true;
	}

	void ValueAnimation_::stop() {
		pause();
		if(!stayAtEnd)
			toBeginning();
	}

	void ThreadCircle(ValueAnimation_* animation)
	{
		while (animation->timerState == Working)
		{
			for (size_t i = 0; i < animation->values.size(); i++)
				animation->values[i].setValue(animation);
			std::this_thread::sleep_for(std::chrono::milliseconds(VALUE_ANIMATION_FREQURENCY));
			animation->nextFrame();
		}
		animation->timerState = Terminated;
	}

	ValueAnimation_::ValueAnimation_(Seconds durationS)
		: mPaused(true), timerState(Working), duration(durationS), position(0), direction(AnimationDirection::Forward),
		repeat(false), stayAtEnd(false), speed(1.0f)
	{
		auto thr = std::thread(ThreadCircle, this);
		thr.detach();
	}

	ValueAnimation_::~ValueAnimation_()
	{
		timerState = PendingToTerminate;
		while (timerState != Terminated)
		{ // Wait for safe thread stopping
		}
	}
}
