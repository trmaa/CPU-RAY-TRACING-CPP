using System;

public class Wall {
	public vec3 position;
	public vec3[] sides = new vec3[2];
	public vec3 normal;
	public Material material = new Material();

	public Wall(vec3 position, vec3[] sides, vec3 col){
		this.position = position;
		this.sides[0] = sides[0];
		this.sides[1] = sides[1];
		this.normal = sides[0].cross(sides[1]).unit();
		this.material.color = col;
	}

	public float colision(Ray ray){
		float D = this.normal.dot(this.position);
		float t = ((D-this.normal.dot(ray.origin))/this.normal.dot(ray.direction));
		vec3 hitp = ray.f(t);
		vec3 w = this.normal/this.normal.dot(this.normal);
		float alpha = w.dot((hitp-this.position).cross(this.sides[1]));
		float beta = w.dot(this.sides[0].cross(hitp-this.position));
		if(alpha > 0 && alpha < 1 && beta > 0 && beta < 1){
			return t;
		} else {
			return 0;
		}
	}
};
