public class Ray{
	public vec3 origin;
	public vec3 direction;

	public Ray(vec3 o, vec3 d){
		this.origin = o;
		this.direction = d;
	}

	public vec3 f(float x){
		return this.origin + this.direction * new vec3(x,x,x);
	}
};