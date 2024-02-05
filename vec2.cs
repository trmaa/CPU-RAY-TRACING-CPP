using System;

public class vec2 {
    public float x, y;

    public vec2(float x, float y) {
        this.x = x;
        this.y = y;
    }

    public float modul() {
        return (float)Math.Sqrt(this.x * this.x + this.y * this.y);
    }

    public float dot(vec2 v) {
        return this.x * v.x + this.y * v.y;
    }

    public static vec2 operator +(vec2 left, vec2 right) {
        return new vec2(left.x + right.x, left.y + right.y);
    }

    public static vec2 operator *(vec2 left, vec2 right) {
        return new vec2(left.x * right.x, left.y * right.y);
    }
}