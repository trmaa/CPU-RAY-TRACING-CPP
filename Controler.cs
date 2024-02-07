using System;
using System.Windows.Forms;

public class Controler {
    public bool wDown = false;
    public bool sDown = false;
    public bool aDown = false;
    public bool dDown = false;
    public bool qDown = false;
    public bool eDown = false;
    public bool uArrow = false;
    public bool dArrow = false;
    public bool lArrow = false;
    public bool rArrow = false;

    public Controler() {
        initializeEventListeners();
    }

    private void initializeEventListeners() {
        App.window.KeyDown += Form_KeyDown;
        App.window.KeyUp += Form_KeyUp;
    }

    private void Form_KeyDown(object sender, KeyEventArgs e) {
        updateKeyState(e.KeyCode, true);
    }

    private void Form_KeyUp(object sender, KeyEventArgs e) {
        updateKeyState(e.KeyCode, false);
    }

    private void updateKeyState(Keys key, bool isDown) {
        switch (key) {
            case Keys.W:
                wDown = isDown;
                break;
            case Keys.S:
                sDown = isDown;
                break;
            case Keys.A:
                aDown = isDown;
                break;
            case Keys.D:
                dDown = isDown;
                break;
            case Keys.ShiftKey:
                qDown = isDown;
                break;
            case Keys.Space:
                eDown = isDown;
                break;
            case Keys.Up:
                uArrow = isDown;
                break;
            case Keys.Down:
                dArrow = isDown;
                break;
            case Keys.Left:
                lArrow = isDown;
                break;
            case Keys.Right:
                rArrow = isDown;
                break;
        }
    }
}