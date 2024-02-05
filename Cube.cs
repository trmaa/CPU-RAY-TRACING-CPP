using System;
using System.Drawing;

public class Cube {
	public static void render(Graphics g){
		App.window.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(1, 1, 6)), new vec2((1280 / App.camara.distance(new vec3(1, 1, 6)) * 0.1f), (1280 / App.camara.distance(new vec3(1, 1, 6)) * 0.1f)));
		App.window.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(-1, 1, 6)), new vec2((1280 / App.camara.distance(new vec3(-1, 1, 6)) * 0.1f), (1280 / App.camara.distance(new vec3(-1, 1, 6)) * 0.1f)));
		App.window.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(1, -1, 6)), new vec2((1280 / App.camara.distance(new vec3(1, -1, 6)) * 0.1f), (1280 / App.camara.distance(new vec3(1, -1, 6)) * 0.1f)));
		App.window.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(-1, -1, 6)), new vec2((1280 / App.camara.distance(new vec3(-1, -1, 6)) * 0.1f), (1280 / App.camara.distance(new vec3(-1, -1, 6)) * 0.1f)));

		App.window.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(1, 1, 4)), new vec2((1280 / App.camara.distance(new vec3(1, 1, 4)) * 0.1f), (1280 / App.camara.distance(new vec3(1, 1, 4)) * 0.1f)));
		App.window.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(-1, 1, 4)), new vec2((1280 / App.camara.distance(new vec3(-1, 1, 4)) * 0.1f), (1280 / App.camara.distance(new vec3(-1, 1, 4)) * 0.1f)));
		App.window.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(1, -1, 4)), new vec2((1280 / App.camara.distance(new vec3(1, -1, 4)) * 0.1f), (1280 / App.camara.distance(new vec3(1, -1, 4)) * 0.1f)));
		App.window.print(g, Color.FromArgb(255, 255, 0, 255), App.camara.project(new vec3(-1, -1, 4)), new vec2((1280 / App.camara.distance(new vec3(-1, -1, 4)) * 0.1f), (1280 / App.camara.distance(new vec3(-1, -1, 4)) * 0.1f)));
	}
};