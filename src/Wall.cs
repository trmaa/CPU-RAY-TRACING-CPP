using System;

public class Wall {
	public vec3 position;
	public vec3[] sides = new vec3[2];
	public Material material = new Material();

	public Wall(vec3 position, vec3[] sides, vec3 col){
		this.position = position;
		this.sides[0] = sides[0];
		this.sides[1] = sides[1];
		this.material.color = col;
	}

	public float colision(Ray ray){
		return 500;
	}
};
