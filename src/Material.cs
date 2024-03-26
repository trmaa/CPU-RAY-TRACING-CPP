public class Material {
	public vec3 color;
	public float roughnes = 0;
	public float emissive = 0;

	public vec3 getEmission(){
		return emissive*color;
	}
};