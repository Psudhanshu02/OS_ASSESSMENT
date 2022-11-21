import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.util.Random;
import javax.swing.JFrame;
import javax.swing.JPanel;
import java.util.concurrent.TimeUnit;

public class SpeedBalls {
    public static void main(String[] args) {
        Model model = new Model();
        View view = new View(model);
        int time = 5, speed = 3;

        view.createAndShowGui();

        for (int i = 0; i < 3; i++) {
            Ball b = new Ball(); // construct a ball
            model.addBall(b); // add it to the model
            b.registerObserver(view.getObserver()); // register view as an observer to it
            new BallAnimator(b, speed); // start a thread to update it

            try {
                TimeUnit.SECONDS.sleep(time);
            } catch (InterruptedException ie) {
                Thread.currentThread().interrupt();
            }
            speed -= 1;
            time += 2;
        }
    }
}

class View {

    BallsPane ballsPane;
    JFrame frame = new JFrame();

    View(Model model) {
        ballsPane = new BallsPane(model);
    }

    void createAndShowGui() {
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLocationRelativeTo(null);
        frame.add(ballsPane);
        frame.pack();
        frame.setResizable(false);
        frame.setVisible(true);
    }

    BallsPane getObserver() {
        return ballsPane;
    }
}

class BallsPane extends JPanel {

    Model model;

    BallsPane(Model model) {
        this.model = model;
        setPreferredSize(new Dimension(300, 200));
    }

    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Ball b = model.getBalls();
        g.setColor(b.color);
        g.fillOval(b.getX(), 190, 10, 10);
    }

    public void onObservableChanged() {
        repaint(); // when a change was notified
    }
}

class Model {
    Ball ball;

    boolean addBall(Ball ball) {
        this.ball = ball;
        return true;
    }

    Ball getBalls() {
        return ball;
    }
}

class Ball {
    int x;
    Color color;
    BallsPane observer; // to be notified on changes

    Ball() {

        Random rnd = new Random();
        color = new Color(rnd.nextInt(256), rnd.nextInt(256), rnd.nextInt(256));
    }

    synchronized int getX() {
        return x;
    }

    synchronized void setX(int x) {
        this.x = x;
        observer.onObservableChanged();
    }

    void registerObserver(BallsPane observer) {
        this.observer = observer;
    }
}

class BallAnimator implements Runnable {

    Ball ball;
    int step;

    BallAnimator(Ball ball, int step) {
        this.ball = ball;
        this.step = step;
        ball.setX(0);
        new Thread(this).start();
    }

    @Override
    public void run() {

        while (true) {

            int newX = ball.getX() + step;

            ball.setX(newX);

            try {
                Thread.sleep(40);
            } catch (InterruptedException ex) {
                ex.printStackTrace();
            }
        }
    }
}
