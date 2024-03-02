using System;

public class Rand{
	private static Random random = new Random();

    public static float Q(){
        return (float)random.NextDouble();
    }
};