#pragma once

#include "Layout.h"
#include <vector>
#include <thread>

#define VALUE_ANIMATION_FREQURENCY 1 // ms

namespace Magenta
{
	typedef double Seconds;

	class ValueAnimation;
	class AnimatedValue
	{
		typedef double* TargetValue;
	public:
		Seconds origin, duration;
		double startValue, endValue;
		TargetValue value;

		void setValue(ValueAnimation* animation);

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

	class ValueAnimation
	{
		std::thread timerThr;
		void nextFrame();
		bool mPaused;
	public:
		AnimationCircleState timerState;

		Seconds duration, position;
		AnimationDirection direction;
		bool repeat;
		double speed;

		bool isPaused() const;

		std::vector<AnimatedValue> values;
		Layout* layoutToUpdate;

		void append(AnimatedValue value);

		void toBeginning();
		void toStart();
		void toEnd();

		void play();
		void playFromBeginning();
		void pause();
		void stop();

		ValueAnimation(Seconds durationMs, Layout* optional = 0);
		~ValueAnimation();
	};
}
