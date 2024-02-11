using System;

public class Light{
	public vec3 normal = new vec3(1,1,1);

	public Light(vec3 direction){
		this.normal = (new vec3(0,0,0)-direction).unit();
	}

	public void orbit() {
	    float angle = (float)Math.Atan2(normal.z, normal.x) + 0.1f;

	    float newX = (float)Math.Cos(angle);
	    float newZ = (float)Math.Sin(angle);

	    this.normal = new vec3(newX, this.normal.y, newZ).unit();
	}
};