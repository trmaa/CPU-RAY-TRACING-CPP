using System;
using System.Drawing;

public class Pixel {
	public Color color = Color.FromArgb(255,255,0,0);
    public vec2 id = new vec2(0, 0);

    public Pixel(Color col ,vec2 id) {
        this.color = col;
        this.id = id;
    }
};