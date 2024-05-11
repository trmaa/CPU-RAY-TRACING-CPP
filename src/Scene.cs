using System;

public class Scene{
	private static Sphere[] sphere = {
		new Sphere(new vec3(0,-1000,0),1000,new vec3(50,255,50)),
        new Sphere(new vec3(0,11,0),10,new vec3(255,255,255)),
        new Sphere(new vec3(-21,11,0),10,new vec3(50,70,255)),
        new Sphere(new vec3(1200,1200,0),1150,new vec3(200,255,255)),
	};

	private static Triangle[] triangle = {
		new Triangle(new vec3(0,0,-100),new vec3[]{new vec3(1,(float)Math.Sqrt(9750),50),new vec3(1,0,100)},new vec3(255,255,255)),
		new Triangle(new vec3(-20,0,-100),new vec3[]{new vec3(1,(float)Math.Sqrt(9750),50),new vec3(1,0,100)},new vec3(255,50,50))
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
		Scene.triangle[1].material.roughnes = 0;
		Scene.sphere[2].material.roughnes = 0;
        Scene.sphere[3].material.emission = 1;
    }
};
