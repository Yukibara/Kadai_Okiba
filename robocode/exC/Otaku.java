package otaota;

import robocode.*;
import java.awt.Color;
import java.lang.Math;;

// API help : http://robocode.sourceforge.net/docs/robocode/robocode/Robot.html

/**
 * Otaku - a robot by (your name here)
 */
public class Otaku extends Robot {
	int jx, jy;
	double px, py;
	enemy en = new enemy();

	/**
	 * run: Otaku's default behavior
	 */
	public void run() {
		// Initialization of the robot should be put here

		// After trying out your robot, try uncommenting the import at the top,
		// and the next line:

		// setColors(Color.BLACK, Color.WHITE, Color.white);
		// body,gun,radar

		// Robot main loop

		// Replace the next 4 lines with any behavior you would like
		field fi = new field(getBattleFieldWidth(), getBattleFieldHeight());
		moveSikaku(fi);

	}

	public void doMoving(double bear, double dis) {
		double t = bear - getHeading();
		System.out.println("t:" + t + ",dis:" + dis);
		boolean baFlag = false;
		if (t > 90) {
			if (t > 180) {
				t -= 360;
			} else {
				t = t - 180;
			}
			turnRight(t);
			back(dis);
		} else if (t < -90) {
			if (t < -180) {
				t += 360;
			} else {
				t = t + 180;
				baFlag = true;
			}
			turnRight(t);
			if (baFlag)
				back(dis);
			else
				ahead(dis);
		} else {
			turnRight(t);
			ahead(dis);
		}
	}

	private void moveTo(double x, double y) {
		double dx = x - getX();
		double dy = y - getY();
		double th = 180 * Math.atan2(dx, dy) / Math.PI;
		double ds = Math.sqrt(dx * dx + dy * dy);
		System.out.println("th:" + th + ",ds:" + ds);
		doMoving(th, ds);
		System.out.println("MoveEnd");
	}

	public void moveSikaku(field fi) {
		double myx = getX();
		double myy = getY();
		double w = fi.width - 30;
		double h = fi.height - 30;
		double x = myx - w / 2;
		double y = myy - h / 2;
		int getaZero = 50;

		while (true) {
			moveTo(w / 2, h); // 上
			moveTo(w, h / 2); // みぎ
			moveTo(w / 2, getaZero); // した
			moveTo(getaZero, h / 2); // ひだり
		}
	}

	public double getAngle(double x, double y) {
		x = Math.abs(x);
		y = Math.abs(y);
		double angle = Math.atan(y / x);
		return (angle * 180 / Math.PI);
	}

	public void tekitoKodo() {
		while (true) {
			ahead(100);
			turnGunRight(360);
			turnGunRight(360);
		}
	}

	public void onWin(WinEvent event) {
		setColors(Color.BLUE, Color.BLUE, Color.BLUE);
	}

	/**
	 * onScannedRobot: What to do when you see another robot
	 */
	public void onScannedRobot(ScannedRobotEvent e) {
		// Replace the next line with any behavior you would like
		double myx = getX();// 自分の位置ｘ座標
		double myy = getY(); // 自分の位置ｙ座標
		double enener = e.getEnergy();// 敵のエネルギーを代入
		double endis = e.getDistance();// 敵との距離を代入
		String enname = e.getName();// 敵の名前を代入
		double enbear = e.getBearing();// 敵のロボとの相対角度
		double radi = roundAngle(getHeading() + enbear);
		int eny = (int) (myy + en.dis * Math.cos(radi * Math.PI / 180));
		int enx = (int) (myx + en.dis * Math.sin(radi * Math.PI / 180));
		en.setEnemyInfo(enx, eny, endis, enener, enname);
	}

	/**
	 * onHitByBullet: What to do when you're hit by a bullet
	 */
	public void onHitByBullet(HitByBulletEvent e) {
		// Replace the next line with any behavior you would like
		back(10);
		setColors(Color.RED, Color.RED, Color.RED);
	}

	/**
	 * onHitWall: What to do when you hit a wall
	 */
	public void onHitWall(HitWallEvent e) {
		// Replace the next line with any behavior you would like
		back(20);
	}

	double roundAngle(double t) {
		while (t < -180 || 180 <= t) {
			if (t < 0) {
				t += 360;
			} else {
				t -= 360;
			}
		}
		return t;
	}
}

class enemy {
	int x, y;
	double dis;
	double ener;
	String name;

	public void setEnemyInfo(int px, int py, double pdis, double pner, String pname) {
		x = px;
		y = py;
		dis = pdis;
		ener = pner;
		name = pname;
	}
}

class field {
	double width, height;

	public field(double w, double h) {
		width = w;
		height = h;
	}

}