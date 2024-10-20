#version 330 core

uniform vec2 u_resolution;
uniform float u_time;

#define M_PI 3.14159265358979323846264338327950288

float random(vec2 st) {
    return fract(sin(dot(st.xy, vec2(14.328520, 42.125))) * 45738.325812);
}


void main() {
    vec2 st = gl_FragCoord.xy/u_resolution.xy;

    float rnd = random(st);

    vec4 color;
    if (rnd > 0.889) {
        color = vec4(1.0, 1.0, 1.0, 0.1);
    } else {
        color = vec4(0.0, 0.0, 0.0, 1.0);
    }

    if (rnd > .988) {
        color.w = rnd * 0.0001 + sin(u_time * M_PI + rnd * 0.001);
    }
    gl_FragColor = color;
}
