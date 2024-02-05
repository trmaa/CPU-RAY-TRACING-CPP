using System;

public class Camara {
    public vec3 position;
    public vec2 angle;

    public Ray[] ray;

    public Camara(){
        ray = new Ray[App.window.pixel.Length];

        foreach (var p in App.window.pixel) {
            ray[(int)(p.id.x + p.id.y * App.window.ClientSize.Width)] = new Ray(
                this.position,
                new vec3(p.id.x, p.id.y, 1)
            );
        }
    }
};