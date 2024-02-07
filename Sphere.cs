public class Sphere {
	public vec3 position;
	public float radius;

	public Sphere(vec3 position, float radius){
		this.position = position;
		this.radius = radius;
	}

	public float colision(Ray ray){
		vec3 oc = ray.origin - this.position;

	    float a = ray.direction.dot(ray.direction);
	    float b = 2 * ray.direction.dot(oc);
	    float c = oc.dot(oc) - this.radius*this.radius;

	    float discriminant = b*b - 4*a*c;

		return discriminant>=0?1:0;
	}
};