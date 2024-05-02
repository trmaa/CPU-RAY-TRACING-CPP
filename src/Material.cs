public class Material {
	public vec3 color;
	public float roughnes = 10;
	public float emission = 0;

	public vec3 getEmission(){
		return emission*color;
	}
};
