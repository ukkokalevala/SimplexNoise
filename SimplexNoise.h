class SimplexNoise {
public:
    float grad(int hash, float x, float y) {
        int h = hash & 7;  // Use lower 3 bits
        float u = h < 4 ? x : y;
        float v = h < 4 ? y : x;
        return ((h & 1) ? -u : u) + ((h & 2) ? -2.0f * v : 2.0f * v);
    }

    float noise(float x, float y) {
        int i0 = (int)floor(x);
        int j0 = (int)floor(y);
        int i1 = i0 + 1;
        int j1 = j0 + 1;

        float x0 = x - i0, y0 = y - j0;
        float x1 = x0 - 1.0f, y1 = y0 - 1.0f;

        float t0 = 1.0f - x0 * x0 - y0 * y0;
        t0 *= t0;
        float n0 = t0 * t0 * grad(hash(i0 + hash(j0)), x0, y0);

        float t1 = 1.0f - x1 * x1 - y0 * y0;
        t1 *= t1;
        float n1 = t1 * t1 * grad(hash(i1 + hash(j0)), x1, y0);

        float t2 = 1.0f - x0 * x0 - y1 * y1;
        t2 *= t2;
        float n2 = t2 * t2 * grad(hash(i0 + hash(j1)), x0, y1);

        float t3 = 1.0f - x1 * x1 - y1 * y1;
        t3 *= t3;
        float n3 = t3 * t3 * grad(hash(i1 + hash(j1)), x1, y1);

        return 0.5f * (n0 + n1 + n2 + n3);
    }

private:
    int hash(int i) {
        i = (i << 13) ^ i;
        return (i * (i * i * 15731 + 789221) + 1376312589) & 0x7FFFFFFF;
    }
};
