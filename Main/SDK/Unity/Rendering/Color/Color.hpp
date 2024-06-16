#pragma once

/*
Source by: https://github.com/clxxe
Modify by: https://github.com/edok3q
If you used this source. Don't forget to credit me as an author
*/

class clr_t {
public:
	float r, g, b, a;
	clr_t( float _r, float _g, float _b, float _a ) : r( _r / 255 ), g( _g / 255 ), b( _b / 255 ), a( _a / 255 ) {}
	clr_t( float _r, float _g, float _b ) : r( _r / 255 ), g( _g / 255 ), b( _b / 255 ), a( 1 ) {}

    static clr_t from_hsb(float hue, float saturation, float brightness) {
        float h = hue == 1.0f ? 0 : hue * 6.0f;
        float f = h - (int)h;
        float p = brightness * (1.0f - saturation);
        float q = brightness * (1.0f - saturation * f);
        float t = brightness * (1.0f - (saturation * (1.0f - f)));

        int i = 0;
        while (i < 6) {
            if (h < i + 1) {
                switch (i) {
                case 0:
                    return clr_t((brightness * 255), (t * 255), (p * 255));
                case 1:
                    return clr_t((q * 255), (brightness * 255), (p * 255));
                case 2:
                    return clr_t((p * 255), (brightness * 255), (t * 255));
                case 3:
                    return clr_t((p * 255), (q * 255), (brightness * 255));
                case 4:
                    return clr_t((t * 255), (p * 255), (brightness * 255));
                case 5:
                    return clr_t((brightness * 255), (p * 255), (q * 255));
                }
            }
            i++;
        }
    }
};