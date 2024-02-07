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
		return this/new vec3(d,d,d);
	}

	public static vec3 operator +(vec3 left, vec3 right) {
        return new vec3(left.x + right.x, left.y + right.y, left.z + right.z);
    }

    public static vec3 operator *(vec3 left, vec3 right) {
        return new vec3(left.x * right.x, left.y * right.y, left.z * right.z);
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