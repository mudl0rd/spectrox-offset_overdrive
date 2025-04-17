#include "easing.h"
#include <math.h>
#include "musys_libc.h"

// Modeled after the line y = x
float LinearInterpolation(float p) {
    return p;
}

// Modeled after the parabola y = x^2
float QuadraticEaseIn(float p) {
    return p * p;
}

// Modeled after the parabola y = -x^2 + 2x
float QuadraticEaseOut(float p) {
    return -(p * (p - 2));
}

// Modeled after the piecewise quadratic
// y = (1/2)((2x)^2)             ; [0, 0.5)
// y = -(1/2)((2x-1)*(2x-3) - 1) ; [0.5, 1]
float QuadraticEaseInOut(float p) {
    if(p < 0.5) {
        return 2 * p * p;
    } else {
        return (-2 * p * p) + (4 * p) - 1;
    }
}

// Modeled after the cubic y = x^3
float CubicEaseIn(float p) {
    return p * p * p;
}

// Modeled after the cubic y = (x - 1)^3 + 1
float CubicEaseOut(float p) {
    float f = (p - 1);
    return f * f * f + 1;
}

// Modeled after the piecewise cubic
// y = (1/2)((2x)^3)       ; [0, 0.5)
// y = (1/2)((2x-2)^3 + 2) ; [0.5, 1]
float CubicEaseInOut(float p) {
    if(p < 0.5) {
        return 4 * p * p * p;
    } else {
        float f = ((2 * p) - 2);
        return 0.5 * f * f * f + 1;
    }
}

// Modeled after the quartic x^4
float QuarticEaseIn(float p) {
    return p * p * p * p;
}

// Modeled after the quartic y = 1 - (x - 1)^4
float QuarticEaseOut(float p) {
    float f = (p - 1);
    return f * f * f * (1 - p) + 1;
}

// Modeled after the piecewise quartic
// y = (1/2)((2x)^4)        ; [0, 0.5)
// y = -(1/2)((2x-2)^4 - 2) ; [0.5, 1]
float QuarticEaseInOut(float p) {
    if(p < 0.5) {
        return 8 * p * p * p * p;
    } else {
        float f = (p - 1);
        return -8 * f * f * f * f + 1;
    }
}

// Modeled after the quintic y = x^5
float QuinticEaseIn(float p) {
    return p * p * p * p * p;
}

// Modeled after the quintic y = (x - 1)^5 + 1
float QuinticEaseOut(float p) {
    float f = (p - 1);
    return f * f * f * f * f + 1;
}

// Modeled after the piecewise quintic
// y = (1/2)((2x)^5)       ; [0, 0.5)
// y = (1/2)((2x-2)^5 + 2) ; [0.5, 1]
float QuinticEaseInOut(float p) {
    if(p < 0.5) {
        return 16 * p * p * p * p * p;
    } else {
        float f = ((2 * p) - 2);
        return  0.5 * f * f * f * f * f + 1;
    }
}

// Modeled after quarter-cycle of sine wave
float SineEaseIn(float p) {
    return musys_sinf((p - 1) * M_PI_2) + 1;
}

// Modeled after quarter-cycle of sine wave (different phase)
float SineEaseOut(float p) {
    return musys_sinf(p * M_PI_2);
}

// Modeled after half sine wave
float SineEaseInOut(float p) {
    return 0.5 * (1 - musys_cosf(p * M_PI));
}

// Modeled after shifted quadrant IV of unit circle
float CircularEaseIn(float p) {
    return 1 - musys_sqrtf(1 - (p * p));
}

// Modeled after shifted quadrant II of unit circle
float CircularEaseOut(float p) {
    return musys_sqrtf((2 - p) * p);
}

// Modeled after the piecewise circular function
// y = (1/2)(1 - sqrt(1 - 4x^2))           ; [0, 0.5)
// y = (1/2)(sqrt(-(2x - 3)*(2x - 1)) + 1) ; [0.5, 1]
float CircularEaseInOut(float p) {
    if(p < 0.5) {
        return 0.5 * (1 - musys_sqrtf(1 - 4 * (p * p)));
    } else {
        return 0.5 * (musys_sqrtf(-((2 * p) - 3) * ((2 * p) - 1)) + 1);
    }
}

// Modeled after the exponential function y = 2^(10(x - 1))
float ExponentialEaseIn(float p) {
    return (p == 0.0) ? p : musys_powf(2, 10 * (p - 1));
}

// Modeled after the exponential function y = -2^(-10x) + 1
float ExponentialEaseOut(float p) {
    return (p == 1.0) ? p : 1 - musys_powf(2, -10 * p);
}

// Modeled after the piecewise exponential
// y = (1/2)2^(10(2x - 1))         ; [0,0.5)
// y = -(1/2)*2^(-10(2x - 1))) + 1 ; [0.5,1]
float ExponentialEaseInOut(float p) {
    if(p == 0.0 || p == 1.0) return p;

    if(p < 0.5) {
        return 0.5 * musys_powf(2, (20 * p) - 10);
    } else {
        return -0.5 * musys_powf(2, (-20 * p) + 10) + 1;
    }
}

// Modeled after the damped sine wave y = sin(13pi/2*x)*pow(2, 10 * (x - 1))
float ElasticEaseIn(float p) {
    return musys_sinf(13 * M_PI_2 * p) * musys_powf(2, 10 * (p - 1));
}

// Modeled after the damped sine wave y = sin(-13pi/2*(x + 1))*pow(2, -10x) + 1
float ElasticEaseOut(float p) {
    return musys_sinf(-13 * M_PI_2 * (p + 1)) * musys_powf(2, -10 * p) + 1;
}

// Modeled after the piecewise exponentially-damped sine wave:
// y = (1/2)*sin(13pi/2*(2*x))*pow(2, 10 * ((2*x) - 1))      ; [0,0.5)
// y = (1/2)*(sin(-13pi/2*((2x-1)+1))*pow(2,-10(2*x-1)) + 2) ; [0.5, 1]
float ElasticEaseInOut(float p) {
    if(p < 0.5) {
        return 0.5 * musys_sinf(13 * M_PI_2 * (2 * p)) * musys_powf(2, 10 * ((2 * p) - 1));
    } else {
        return 0.5 * (musys_sinf(-13 * M_PI_2 * ((2 * p - 1) + 1)) * musys_powf(2, -10 * (2 * p - 1)) + 2);
    }
}

// Modeled after the overshooting cubic y = x^3-x*sin(x*pi)
float BackEaseIn(float p) {
    return p * p * p - p * musys_sinf(p * M_PI);
}

// Modeled after overshooting cubic y = 1-((1-x)^3-(1-x)*sin((1-x)*pi))
float BackEaseOut(float p) {
    float f = (1 - p);
    return 1 - (f * f * f - f * musys_sinf(f * M_PI));
}

// Modeled after the piecewise overshooting cubic function:
// y = (1/2)*((2x)^3-(2x)*sin(2*x*pi))           ; [0, 0.5)
// y = (1/2)*(1-((1-x)^3-(1-x)*sin((1-x)*pi))+1) ; [0.5, 1]
float BackEaseInOut(float p) {
    if(p < 0.5) {
        float f = 2 * p;
        return 0.5 * (f * f * f - f * musys_sinf(f * M_PI));
    } else {
        float f = (1 - (2*p - 1));
        return 0.5 * (1 - (f * f * f - f * musys_sinf(f * M_PI))) + 0.5;
    }
}

float BounceEaseIn(float p) {
    return 1 - BounceEaseOut(1 - p);
}

float BounceEaseOut(float p) {
    if(p < 4/11.0) {
        return (121 * p * p)/16.0;
    } else if(p < 8/11.0) {
        return (363/40.0 * p * p) - (99/10.0 * p) + 17/5.0;
    } else if(p < 9/10.0) {
        return (4356/361.0 * p * p) - (35442/1805.0 * p) + 16061/1805.0;
    } else {
        return (54/5.0 * p * p) - (513/25.0 * p) + 268/25.0;
    }
}

float BounceEaseInOut(float p) {
    if(p < 0.5) {
        return 0.5 * BounceEaseIn(p*2);
    } else {
        return 0.5 * BounceEaseOut(p * 2 - 1) + 0.5;
    }
}
