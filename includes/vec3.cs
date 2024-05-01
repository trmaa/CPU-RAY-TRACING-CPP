using System;

public class vec3{
	public float x, y, z;

	public vec3(float x, float y, float z){
		this.x = x;
		this.y = y;
		this.z = z;
	}

	public float modul(){
		return (float)Math.Sqrt(this.x*this.x+this.y*this.y+this.z*this.z);
	}

	public float dot(vec3 v){
		return (float)(this.x*v.x+this.y*v.y+this.z*v.z);
	}

	public vec3 unit(){
	    float d = this.modul();
	    if (d != 0)
	        return this * (1/d);
	    else
	        return new vec3(0, 0, 0);
	}

	public vec3 cunit(){
		vec3 raw = (float)Math.Sqrt(3)*this.unit();
		raw.x = raw.x>1?1:raw.x<0?0:raw.x;
		raw.y = raw.y>1?1:raw.x<0?0:raw.y;
		raw.z = raw.z>1?1:raw.x<0?0:raw.z;
		return raw;
	}

	public vec3 cross(vec3 v){
		float crossX = (this.y * v.z) - (this.z * v.y);
        float crossY = (this.z * v.x) - (this.x * v.z);
        float crossZ = (this.x * v.y) - (this.y * v.x);
        
        return new vec3(crossX, crossY, crossZ);
	}

	public static bool operator >=(vec3 left, vec3 right){
		return (left.x>=right.x&&left.y>=right.y&&left.z>=right.z);
	}

	public static bool operator <=(vec3 left, vec3 right){
		return (left.x<=right.x&&left.y<=right.y&&left.z<=right.z);
	}

	public static vec3 operator +(vec3 left, vec3 right) {
        return new vec3(left.x + right.x, left.y + right.y, left.z + right.z);
    }

    public static vec3 operator +(float left, vec3 right) {
        return new vec3(left + right.x, left + right.y, left + right.z);
    }

    public static vec3 operator *(vec3 left, vec3 right) {
        return new vec3(left.x * right.x, left.y * right.y, left.z * right.z);
    }

    public static vec3 operator *(float left, vec3 right) {
        return new vec3(left * right.x, left * right.y, left * right.z);
    }

    public static vec3 operator *(vec3 right, float left) {
        return new vec3(left * right.x, left * right.y, left * right.z);
    }

    public static vec3 operator -(vec3 left, vec3 right) {
	    return new vec3(left.x - right.x, left.y - right.y, left.z - right.z);
	}

	public static vec3 operator /(vec3 left, vec3 right) {
	    if (right.x != 0 && right.y != 0 && right.z != 0) {
	        return new vec3(left.x / right.x, left.y / right.y, left.z / right.z);
	    } else {
	        return new vec3(float.NaN, float.NaN, float.NaN);
	    }
	}
};
