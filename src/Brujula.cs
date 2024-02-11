using System;
using System.Drawing;

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

  public static void render(Graphics g){
    Brujula.update();
    App.window.println(g,
        App.camara.project(Brujula.position) + new vec2((float)(App.window.ClientSize.Width * 0.5 - 100), (float)(100 - App.window.ClientSize.Height * 0.5)),
        App.camara.project(new vec3(Brujula.position.x, Brujula.position.y, Brujula.vertex.z)) + new vec2((float)(App.window.ClientSize.Width * 0.5 - 100), (float)(100 - App.window.ClientSize.Height * 0.5)),
        3, Color.Blue
    );
    App.window.println(g,
        App.camara.project(Brujula.position) + new vec2((float)(App.window.ClientSize.Width * 0.5 - 100), (float)(100 - App.window.ClientSize.Height * 0.5)),
        App.camara.project(new vec3(Brujula.vertex.x, Brujula.position.y, Brujula.position.z)) + new vec2((float)(App.window.ClientSize.Width * 0.5 - 100), (float)(100 - App.window.ClientSize.Height * 0.5)),
        3, Color.Red
    );
    App.window.println(g,
        App.camara.project(Brujula.position) + new vec2((float)(App.window.ClientSize.Width * 0.5 - 100), (float)(100 - App.window.ClientSize.Height * 0.5)),
        App.camara.project(new vec3(Brujula.position.x, Brujula.vertex.y, Brujula.position.z)) + new vec2((float)(App.window.ClientSize.Width * 0.5 - 100), (float)(100 - App.window.ClientSize.Height * 0.5)),
        3, Color.Green
    );
  }
}