package otaota;

import robocode.*;
import java.awt.Color;
import java.lang.Math;
import static robocode.util.Utils.normalRelativeAngleDegrees;

// API help : http://robocode.sourceforge.net/docs/robocode/robocode/Robot.html

/**
 * Otaku - a robot by (your name here)
 */
public class Otaku extends AdvancedRobot {
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
		setAdjustRadarForGunTurn(true);
		setAdjustGunForRobotTurn(true);
		setAdjustRadarForRobotTurn(true);

		field fi = new field(getBattleFieldWidth(), getBattleFieldHeight());
		moveCircle(fi);
	}

	public void moveCircle(field fi) {
		double w = fi.width - 150;
		double h = fi.height - 150;
		double getaZero = 50;
		turnLeft(getHeading());
		turnRadarLeft(getRadarHeading());
		out.println("Hello");
		turnRadarRight(360);
		out.println("x:" + en.x + "y" + en.y);
		moveTo(en.x - 100, en.y + 50);
		setAhead(100000);
	}

	boolean baFlag;
	boolean doneMove = false;

	public void doMoving(double bear, double dis) {
		double t = bear - getHeading();
		System.out.println("t:" + t + ",dis:" + dis);

		baFlag = false;
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
		turnLeft(getHeading());
		doneMove = true;
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

	public void onWin(WinEvent event) {
		setColors(Color.BLUE, Color.BLUE, Color.BLUE);
	}

	private void radarTo(double x, double y) {
		double dx = x - getX();
		double dy = y - getY();
		double th = 180 * Math.atan2(dx, dy) / Math.PI;
		double t = th - getRadarHeading();
		if (t > 90) {
			if (t > 180) {
				t -= 360;
			} else {
				t = t - 180;
			}
			setTurnRadarRight(t);
		} else if (t < -90) {
			if (t < -180) {
				t += 360;
			} else {
				t = t + 180;
			}
			setTurnRadarRight(t);
		} else {
			setTurnRadarRight(t);
		}
	}

	boolean enemyCatch = false;

	/**
	 * onScannedRobot: What to do when you see another robot
	 */
	public void onScannedRobot(ScannedRobotEvent e) {
		// Replace the next line with any behavior you would like
		out.println("Scanning Enemy!");
		double myx = getX();// 自分の位置ｘ座標
		double myy = getY(); // 自分の位置ｙ座標
		double enener = e.getEnergy();// 敵のエネルギーを代入
		double endis = e.getDistance();// 敵との距離を代入
		String enname = e.getName();// 敵の名前を代入
		double enbear = e.getBearing();// 敵のロボとの相対角度
		double radi = roundAngle(getHeading() + enbear);
		double eny = (myy + endis * Math.cos(Math.toRadians(enbear)));
		double enx = (myx + endis * Math.sin(Math.toRadians(enbear)));
		// out.println("enx :" + enx + "eny :" + eny);
		en.setEnemyInfo(enx, eny, endis, enener, enname);
		// if (!enemyCatch) {
		// moveTo(enx - 50, eny + 100);
		// enemyCatch = true;
		// }
		// radarTo(enx, eny);
		double absoKakudo = getHeading() + e.getBearing();
		double rotateRadar = normalRelativeAngleDegrees(absoKakudo - getRadarHeading());
		setTurnRadarRight(rotateRadar);
		if (doneMove) {
			setTurnRight(normalRelativeAngleDegrees(en.ener));
			setTurnRight(normalRelativeAngleDegrees(en.ener));

		}
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

// 敵の情報
class enemy {
	double x, y;
	double dis;
	double ener;
	String name;

	public void setEnemyInfo(double px, double py, double pdis, double pner, String pname) {
		x = px;
		y = py;
		dis = pdis;
		ener = pner;
		name = pname;
	}
}

// フィールド情報
class field {
	double width, height;

	public field(double w, double h) {
		width = w;
		height = h;
	}

}