using System;

public class Brujula{
  public static vec3 position = new vec3(0,0,0);
  public static vec3 vertex = new vec3(0,0,0);

  public static void update(){
    Brujula.position = new vec3(
      (float)(App.camara.position.x+Math.Cos(App.camara.angle.y)*Math.Cos(App.camara.angle.x)*1000),
      (float)(App.camara.position.y+Math.Sin(App.camara.angle.x)*1000),
      (float)(App.camara.position.z+Math.Sin(App.camara.angle.y)*Math.Cos(App.camara.angle.x)*1000)
    );

    Brujula.vertex = new vec3(
      Brujula.position.x+50,
      Brujula.position.y+50,
      Brujula.position.z+50
    );
  }
}