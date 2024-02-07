public class Sphere {
	public static vec3 position = new vec3(0,0,5);
	public static vec3 radius = new vec3(1,1,1);

	public static float colision(Ray ray){
		vec3 oc = ray.origin - Sphere.position;

	    float a = ray.direction.dot(ray.direction);
	    float b = 2 * ray.direction.dot(oc);
	    float c = oc.dot(oc) - radius.modul()*radius.modul();

	    float discriminant = b*b - 4*a*c;

		return discriminant>=0?1:0;
	}
};