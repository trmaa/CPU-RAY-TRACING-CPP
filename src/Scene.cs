using System;

public class Scene{
	private static Sphere[] sphere = {	
	};

	private static Triangle[] triangle = {
		new Triangle(new vec3(0,0,-100),new vec3[]{new vec3(1,(float)Math.Sqrt(9750),50),new vec3(1,0,100)},new vec3(255,255,255))
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
		Scene.triangle[0].material.emission = 1;
    }
};
