#pragma once

/**
 * @brief TimeStep holds a fixed simulation step in seconds.
 *
 * Use a fixed step for deterministic gameplay; render may interpolate.
 */
struct TimeStep {
    double seconds { 1.0 / 60.0 };  ///< Fixed simulation step, default 60 Hz
};

/** 
 * @brief FrameClock tracks wall time accumulation for fixed-step updates.
 *
 * Accumulator pattern: add delta, run N updates of fixed size, carry remainder.
 */
class FrameClock {
public:
    /// Add elapsed seconds sinrce the last frame; return how many fixed steps to process.
    int accumulate(double dt, const TimeStep& step) {
        accumulator_ += dt;
        int steps = static_cast<int>(accumulator_ / step.seconds);
        accumulator_ -= steps * step.seconds;
        return steps;
    }

    /// Fraction [0, 1) of how far we are to the next simulation step; useful for render interpolation.
    double alpha(const TimeStep& step) const {
        if (step.seconds <= 0.0) return 0.0;
        return accumulator_ / step.seconds;
    }

    /// Clear accumulator; call on resize or pause.
    void reset() { accumulator_ = 0.0; }

private:
    double accumulator_ { 0.0 };
};
