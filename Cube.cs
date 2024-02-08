using System;
using System.Drawing;

public class Cube {
	public static vec3 position = new vec3(0,0,5);
	public static vec3 radius = new vec3(1,1,1);

	public static void render(Graphics g){
		App.window.print(g, Color.FromArgb(255, 255, 255, 255), App.camara.project(Cube.position + new vec3(1, 1, 1)*Cube.radius), new vec2((1280 / App.camara.distance(Cube.position + new vec3(1, 1, 1)*Cube.radius) * 0.1f), (1280 / App.camara.distance(Cube.position + new vec3(1, 1, 1)*Cube.radius) * 0.1f)));
		App.window.print(g, Color.FromArgb(255, 255, 255, 255), App.camara.project(Cube.position + new vec3(-1, 1, 1)*Cube.radius), new vec2((1280 / App.camara.distance(Cube.position + new vec3(-1, 1, 1)*Cube.radius) * 0.1f), (1280 / App.camara.distance(Cube.position + new vec3(-1, 1, 1)*Cube.radius) * 0.1f)));
		App.window.print(g, Color.FromArgb(255, 255, 255, 255), App.camara.project(Cube.position + new vec3(1, -1, 1)*Cube.radius), new vec2((1280 / App.camara.distance(Cube.position + new vec3(1, -1, 1)*Cube.radius) * 0.1f), (1280 / App.camara.distance(Cube.position + new vec3(1, -1, 1)*Cube.radius) * 0.1f)));
		App.window.print(g, Color.FromArgb(255, 255, 255, 255), App.camara.project(Cube.position + new vec3(-1, -1, 1)*Cube.radius), new vec2((1280 / App.camara.distance(Cube.position + new vec3(-1, -1, 1)*Cube.radius) * 0.1f), (1280 / App.camara.distance(Cube.position + new vec3(-1, -1, 1)*Cube.radius) * 0.1f)));

		App.window.print(g, Color.FromArgb(255, 255, 255, 255), App.camara.project(Cube.position + new vec3(1, 1, -1)*Cube.radius), new vec2((1280 / App.camara.distance(Cube.position + new vec3(1, 1, -1)*Cube.radius) * 0.1f), (1280 / App.camara.distance(Cube.position + new vec3(1, 1, -1)*Cube.radius) * 0.1f)));
		App.window.print(g, Color.FromArgb(255, 255, 255, 255), App.camara.project(Cube.position + new vec3(-1, 1, -1)*Cube.radius), new vec2((1280 / App.camara.distance(Cube.position + new vec3(-1, 1, -1)*Cube.radius) * 0.1f), (1280 / App.camara.distance(Cube.position + new vec3(-1, 1, -1)*Cube.radius) * 0.1f)));
		App.window.print(g, Color.FromArgb(255, 255, 255, 255), App.camara.project(Cube.position + new vec3(1, -1, -1)*Cube.radius), new vec2((1280 / App.camara.distance(Cube.position + new vec3(1, -1, -1)*Cube.radius) * 0.1f), (1280 / App.camara.distance(Cube.position + new vec3(1, -1, -1)*Cube.radius) * 0.1f)));
		App.window.print(g, Color.FromArgb(255, 255, 255, 255), App.camara.project(Cube.position + new vec3(-1, -1, -1)*Cube.radius), new vec2((1280 / App.camara.distance(Cube.position + new vec3(-1, -1, -1)*Cube.radius) * 0.1f), (1280 / App.camara.distance(Cube.position + new vec3(-1, -1, -1)*Cube.radius) * 0.1f)));

		App.window.print(g, Color.FromArgb(255, 0, 255, 255), App.camara.project(Cube.position), new vec2((1280 / App.camara.distance(Cube.position) * 0.1f), (1280 / App.camara.distance(Cube.position) * 0.1f)));
	}
};