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

    public vec2 unit(){
        float d = this.modul();
        if (d != 0)
            return this / new vec2(d, d);
        else
            return new vec2(0, 0);
    }

    public static vec2 operator +(vec2 left, vec2 right) {
        return new vec2(left.x + right.x, left.y + right.y);
    }

    public static vec2 operator +(float left, vec2 right) {
        return new vec2(left + right.x, left + right.y);
    }

    public static vec2 operator *(vec2 left, vec2 right) {
        return new vec2(left.x * right.x, left.y * right.y);
    }

    public static vec2 operator -(vec2 left, vec2 right) {
	    return new vec2(left.x - right.x, left.y - right.y);
	}

	public static vec2 operator /(vec2 left, vec2 right) {
	    if (right.x != 0 && right.y != 0) {
	        return new vec2(left.x / right.x, left.y / right.y);
	    } else {
	        return new vec2(float.NaN, float.NaN);
	    }
	}
}