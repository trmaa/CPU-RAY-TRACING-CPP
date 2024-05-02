using System;

public class Scene{
	private static Sphere[] sphere = {	
		//new Sphere(new vec3(-20,12,20),5,new vec3(255,255,255))
	};

	private static Triangle[] triangle = {
		//new Triangle(new vec3(-1000,0,-1000),new vec3[]{new vec3(1000,1,2000),new vec3(2000,0,0)},new vec3(255,255,255)),
		new Triangle(new vec3(-20,-20,-20),new vec3[]{new vec3(1,80,40),new vec3(2,0,80)},new vec3(255,255,255)),
		new Triangle(new vec3(0,0,0),new vec3[]{new vec3(1,40,20),new vec3(2,0,40)},new vec3(255,255,255)),
		new Triangle(new vec3(20,-20,-20),new vec3[]{new vec3(1,80,40),new vec3(2,0,80)},new vec3(255,255,255))
	};

	public static Func<int> elementn = () => Scene.sphere.Length + Scene.triangle.Length;

	public static dynamic element(int i){
		if(i<Scene.sphere.Length){
			return Scene.sphere[i];
		} else {
			return Scene.triangle[i-Scene.sphere.Length];
		}
	}

	public static void start(){
		Scene.triangle[2].material.emission = 1;
    }
};
