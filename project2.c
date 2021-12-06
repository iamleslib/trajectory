#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include<stdio.h>
#include<math.h>

int main()
{

	//---> DETERMINING PLANET AND SETTING GRAVITY <---//
	int userVal;

	printf("Pumpkin Projectile Calculator\n");
	printf("Which plant are you on?\n\n");
	
	printf("\t1 - Earth\n\t2 - Mars\n\t3 - Venus\n\n");
	
	printf("Please type your selection number and press enter:\n");
	scanf("%d", &userVal);

	
	while (!((userVal == 1) || (userVal == 2) || (userVal == 3)))
	{
		printf("\nError. Please enter an integer value between 1 and 3:\n");
		scanf("%d", &userVal);

	}

	double gravity;

	switch (userVal)
	{
		case 1:	//Earth
			gravity = 9.798;	//meters per second squared
			break;
		case 2: //Mars
			gravity = 3.71;		//meters per second squared
			break;
		case 3: //Venus 
			gravity = 8.87;		//meters per second squared
			break;
	}

	printf("The gravitational acceleration on your planet is %.4f m/sec/sec.\n", gravity);

	//----------------------END----------------------//

	//---> USER INPUT FOR LAUNCH DETAILS <---//

	double launchAngle;		//degrees
	double launchVelocity;	//meters per second
	double relativeHeight;	//meters

	printf("What is the launch angle (degrees)? ");
	scanf("%lf", &launchAngle);
	while ((launchAngle < 0) || (launchAngle > 90))
	{
		printf("\nError. The angle must be between 0 and 90 degrees:");
		scanf("%lf", &launchAngle);
	}

	printf("What is the initial velocity (m/s)? ");
	scanf("%lf", &launchVelocity);
	while (launchVelocity < 0)
	{
		printf("\nError. The launch velocity must be greater that 0 meters per second:");
		scanf("%lf",& launchVelocity);
	}
	printf("What is the relative height of the launch point (m)? ");
	scanf("%lf", &relativeHeight);
	while ((relativeHeight < -10) || (relativeHeight > 10))
	{
		printf("\nError. The relative height of the launch point must be between -10 meters and 10 meters:");
		scanf("%lf", &relativeHeight);
	}

	//Converting launch angle from degrees to radians
	double launchAngleRadians = launchAngle * (M_PI / 180);

	printf("\n\nLaunch angle is %.4f degrees (%.4f radians).", launchAngle, launchAngleRadians);
	printf("\nLaunch velocity is %.4f m/sec.", launchVelocity);
	printf("\nRelative height of launch point is %.4f m.", relativeHeight);

	//-----------------END-----------------//

	//---> COMPUTING APEX, RANGE AND TOTAL FLIGHT TIME <---//

	double apex;	//H
	double range;	//R
	double totalTime;	//T

	//Scenario A ---> launch point and target area are the same height
	if (relativeHeight == 0)
	{
		apex = (pow(launchVelocity, 2) * pow(sin(launchAngleRadians), 2)) / (2 * gravity);
		totalTime = (2 * launchVelocity * sin(launchAngleRadians)) / gravity;
		range = launchVelocity * totalTime * cos(launchAngleRadians);
	}
	//Scenario B ---> target area is higher than launch point
	else if (relativeHeight > 0)
	{
		apex = (pow(launchVelocity, 2) * pow(sin(launchAngleRadians), 2)) / (2 * gravity);
		totalTime = ((launchVelocity * sin(launchAngleRadians)) / gravity) + (sqrt((2*(apex - relativeHeight)))/gravity);
		range = launchVelocity * totalTime * cos(launchAngleRadians);
	}
	//Scenario C ---> target area is lower than launch point
	else
	{
		apex = fabs(relativeHeight) + (pow(launchVelocity, 2) * pow(sin(launchAngleRadians), 2)) / (2 * gravity);
		totalTime = ((launchVelocity * sin(launchAngleRadians)) / gravity) + (sqrt(2 * apex / gravity));
		range = launchVelocity * totalTime * cos(launchAngleRadians);
	}

	printf("\n\nApex of the trajectory is %.4f m.", apex);
	printf("\nRange from launch to target is %.4f m.", range);
	printf("\nTotal flight time to target is %.4f sec.\n\n", totalTime);
	//-------------------------END--------------------------//

	//---> GENERATING TRAJECTORY TABLE <---//
	
	printf("Pumpkin Trajectory:\n\n");
	printf("\t     Time   X-Distance  Y-Height  Y-Velocity  Velocity\n");
	double currentTime;
	for (currentTime = 0; currentTime < totalTime; currentTime += totalTime/20)
	{
		double x = launchVelocity*currentTime*cos(launchAngleRadians);	//current horizontal position
		double y = (launchVelocity*currentTime*sin(launchAngleRadians)) - ((gravity*pow(currentTime,2))/2);	//current verticle position
		double velocity_y = (launchVelocity*sin(launchAngleRadians)) - (gravity*currentTime);	//verticle velocity
		double velocity = sqrt(pow(launchVelocity, 2) - (2*gravity*currentTime*launchVelocity*sin(launchAngleRadians)) + (pow(gravity, 2)*pow(currentTime, 2)));	//overall velocity
	
		printf("\t %8.3f     %8.3f  %8.3f    %8.3f  %8.3f\n", currentTime, x, y, velocity_y, velocity);
	
	}
	//---------------END-------------------//



	return 0;
}