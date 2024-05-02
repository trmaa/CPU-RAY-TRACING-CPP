using System;

public class Triangle {
	public vec3 position;
	public vec3[] sides = new vec3[2];
	public vec3 normal;
	public Material material = new Material();

	public Triangle(vec3 position, vec3[] sides, vec3 col){
		this.position = position;
		this.sides[0] = sides[0];
		this.sides[1] = sides[1];
		this.normal = sides[0].cross(sides[1]).unit();
		this.material.color = col;
	}

	public float colision(Ray ray){
		float D = this.normal.dot(this.position);
		float t = ((D-this.normal.dot(ray.origin))/this.normal.dot(ray.direction));

		if(t > 0){
			vec3 hitp = ray.f(t);
			
			vec3 A = this.position;
			vec3 B = this.sides[0] + A;
			vec3 C = this.sides[1] + A;

			vec3 BA = A - B;
			vec3 BC = C - B;
			vec3 BH = hitp - B;

			float ABC = (float)Math.Acos(BA.dot(BC) / (BA.modul() * BC.modul()));

			float a = ((BC.y * BH.x) - (BC.x * BH.y)) / ((BC.y * BA.x) - (BC.x * BA.y));
			float b = ((BA.y * BH.x) - (BA.x * BH.y)) / ((BA.y * BC.x) - (BA.x * BC.y));

			if (a >= 0 && b >= 0 && (a + b) <= 1){
				return t;
			}else{
				return 0;
			}
		} else {
			return 0;
		}
	}
};
