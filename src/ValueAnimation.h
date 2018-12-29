#pragma once

#include <vector>
#include <future>

#define VALUE_ANIMATION_FREQURENCY 1 // ms

namespace Magenta
{
	typedef double Seconds;

	class ValueAnimation_;
	class AnimatedValue
	{
		typedef double& TargetValue;
	public:
		Seconds origin, duration;
		double startValue, endValue;
		TargetValue value;

		void setValue(ValueAnimation_* animation);

		AnimatedValue(TargetValue target, double startVal, double endVal, Seconds durationS, Seconds originS = 0);
	};

	typedef enum {
		Forward,
		ForwardReverse,
		Backward,
		BackwardReverse,
	} AnimationDirection;

	typedef enum {
		Working,
		PendingToTerminate,
		Terminated
	} AnimationCircleState;

	class ValueAnimation_
	{
		bool mPaused;
	public:
		AnimationCircleState timerState;

		Seconds duration, position;
		AnimationDirection direction;
		bool repeat;
		double speed;

		void nextFrame();

		bool isPaused() const;

		std::vector<AnimatedValue> values;

		void append(AnimatedValue value);

		void toBeginning();
		void toStart();
		void toEnd();

		void play();
		void playFromBeginning();
		void pause();
		void stop();

		ValueAnimation_(Seconds durationS);
		~ValueAnimation_();
	};

	typedef ValueAnimation_& ValueAnimation;
}
