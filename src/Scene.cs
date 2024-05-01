using System;

public class Scene{
	public static Sphere[] sphere = {
        new Sphere(new vec3(0,-1000,0),1000,new vec3(50,255,50)),
        new Sphere(new vec3(0,11,0),10,new vec3(255,255,255)),
        new Sphere(new vec3(21,11,0),10,new vec3(255,50,50)),
        new Sphere(new vec3(-21,11,0),10,new vec3(50,70,255)),
        new Sphere(new vec3(1200,1500,0),1450,new vec3(200,255,255)),
        new Sphere(new vec3(-1300,0,1200),1000,new vec3(255,50,70))
    };

	public static Func<int> elementn = () => Scene.sphere.Length;
	public static Func<Sphere[]> element = () => Scene.sphere;

	public static void start(){
        Scene.sphere[1].material.roughnes = 1;
        Scene.sphere[2].material.roughnes = 10;
        Scene.sphere[0].material.roughnes = 10;
        Scene.sphere[4].material.emission = 1;
        Scene.sphere[5].material.emission = 1;
    }
};
