using System;

public class Ray{
	public vec3 idleD;
	public vec3 idleA;
	public vec3 origin;
	public vec3 direction;

	public Ray(vec3 o, vec3 d){
		this.origin = o;
		this.direction = d;
		this.idleD = d;
        this.idleA = new vec3(
        	(float)Math.Atan2(d.y,d.z),
        	(float)Math.Atan2(d.x,d.z),
        	0
        );
	}

	public vec3 f(float x){
		return this.origin + this.direction * x;
	}
};