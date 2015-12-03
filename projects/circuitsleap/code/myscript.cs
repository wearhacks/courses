/******************************************************************************\
* Copyright (C) 2012-2014 Leap Motion, Inc. All rights reserved.               *
* Leap Motion proprietary and confidential. Not for distribution.              *
* Use subject to the terms of the Leap Motion SDK Agreement available at       *
* https://developer.leapmotion.com/sdk_agreement, or another agreement         *
* between Leap Motion and you, your company or other organization.             *
\******************************************************************************/
using System;
using System.Threading;
using Leap;
using UnityEngine;
using System.Collections;

public class Clicktime //This is the global variable, don't touch anything inside
{ 
	public static float clicktime = 0;
	public static char gesture;
	public static char square;
	public static int element_place_x = 0;
	public static int element_place_y = 0;
	public static float xi = 0;
	public static float yi = 0;
	public static float xf = 0;
	public static float yf = 0;
	public static float k = -100;
	public static float finali = 0;
	public static float finalj = 0;
	public static bool IsPinch = false;
	public static bool IsLeft = false;
	public static bool IsRight = false;
	public static int location1 = 0;
	public static int location2 = 0;
} 
public class myscript: MonoBehaviour{

	public class Element //This is the class for each coordinate box
	{
		public int nx { get; set; }
		public int ny { get; set; }
		public Element(int Nx, int Ny)
		{
			nx = Nx;
			ny = Ny;
		}


	}
		
	public GameObject Inductor_im;//I
	public GameObject Power_im; //P
	public GameObject Resistor_im;//R
	public GameObject Capacitor_im;//C
	
	GameObject inductor_im;
	GameObject power_im;
	GameObject resistor_im;
	GameObject capacitor_im;

	public float cooldown = 1;
	Element A = new Element(20,20);
	Element B = new Element(-20, 20);
	Element C = new Element(20, -20);
	Element D = new Element(-20,-20);

	void Start(){
	}
	
	void Update(){

		SampleListener listener = new SampleListener ();
		Controller controller = new Controller ();

		controller.AddListener (listener);

		controller.RemoveListener (listener);
		controller.Dispose ();

		//Clicktime.clicktime += Time.deltaTime;


		//if (Clicktime.clicktime > cooldown){
		approximateposition (Clicktime.finali, Clicktime.finalj);
		switch (Clicktime.gesture) {
		case 'c':
			//SpawnInductor (20,20, Clicktime.k);
			SpawnInductor (Clicktime.finali, Clicktime.finalj, -100);
			Debug.Log ("Spawning inductor");
			break;
		case 'k':
			//SpawnCapacitor(20,-20,Clicktime.k);
			SpawnCapacitor (Clicktime.finali, Clicktime.finalj, -100);
			Debug.Log ("Spawning capacitor");
			break;
		case 's':
			//SpawnResistor(-20,20,Clicktime.k);
			SpawnResistor (Clicktime.finali, Clicktime.finalj, -100);
			Debug.Log ("Spawning resistor");
			break;
		case 'w':
			//SpawnPower (-20,-20,Clicktime.k);
			SpawnPower (Clicktime.finali, Clicktime.finalj, -100);
			Debug.Log ("Spawning power");
			break;
		case 'p':
			if (Clicktime.location1 == 0) {
				if (Clicktime.IsLeft == true) { // if there is no first location and left node is indicated
					if (Clicktime.finali == A.nx & Clicktime.finalj == A.ny) { // CaseA
						Clicktime.xi = A.nx1;
						Clicktime.yi = A.ny1;
					} else if (Clicktime.finali == B.nx & Clicktime.finalj == B.ny) { // CaseB
						Clicktime.xi = B.nx1;
						Clicktime.yi = B.ny1;
					} else if (Clicktime.finali == C.nx & Clicktime.finalj == C.ny) { // CaseC
						Clicktime.xi = C.nx1;
						Clicktime.yi = C.ny1;
					} else if (Clicktime.finali == D.nx & Clicktime.finalj == D.ny) { // CaseD
						Clicktime.xi = D.nx1;
						Clicktime.yi = D.ny1;
					} 
				} else if (Clicktime.IsRight == true) {
					// if there is no first location and right node is indicated
					if (Clicktime.finali == A.nx & Clicktime.finalj == A.ny) { // CaseA
						Clicktime.xi = A.nx2;
						Clicktime.yi = A.ny1;
					} else if (Clicktime.finali == B.nx & Clicktime.finalj == B.ny) { // CaseB
						Clicktime.xi = B.nx2;
						Clicktime.yi = B.ny1;
					} else if (Clicktime.finali == C.nx & Clicktime.finalj == C.ny) { // CaseC
						Clicktime.xi = C.nx2;
						Clicktime.yi = C.ny1;
					} else if (Clicktime.finali == D.nx & Clicktime.finalj == D.ny) { // CaseD
						Clicktime.xi = D.nx2;
						Clicktime.yi = D.ny1;
					} 
				}
				Clicktime.location1 = 1;
			}
			if (Clicktime.location1 != 0) {
				if (Clicktime.IsLeft == true) { // if there is first location and left node is indicated
					if (Clicktime.finali == A.nx & Clicktime.finalj == A.ny) { // CaseA
						Clicktime.xf = A.nx1;
						Clicktime.yf = A.ny1;
					} else if (Clicktime.finali == B.nx & Clicktime.finalj == B.ny) { // CaseB
						Clicktime.xf = B.nx1;
						Clicktime.yf = B.ny1;
					} else if (Clicktime.finali == C.nx & Clicktime.finalj == C.ny) { // CaseC
						Clicktime.xf = C.nx1;
						Clicktime.yf = C.ny1;
					} else if (Clicktime.finali == D.nx & Clicktime.finalj == D.ny) { // CaseD
						Clicktime.xf = D.nx1;
						Clicktime.yf = D.ny1;
					}
				} else if (Clicktime.IsRight == true) {
					// if there is first location and right node is indicated
					if (Clicktime.finali == A.nx & Clicktime.finalj == A.ny) { // CaseA
						Clicktime.xf = A.nx2;
						Clicktime.yf = A.ny1;
					} else if (Clicktime.finali == B.nx & Clicktime.finalj == B.ny) { // CaseB
						Clicktime.xf = B.nx2;
						Clicktime.yf = B.ny1;
					} else if (Clicktime.finali == C.nx & Clicktime.finalj == C.ny) { // CaseC
						Clicktime.xf = C.nx2;
						Clicktime.yf = C.ny1;
					} else if (Clicktime.finali == D.nx & Clicktime.finalj == D.ny) { // CaseD
						Clicktime.xf = D.nx2;
						Clicktime.yf = D.ny1;
					}
				}
				Clicktime.location2 = 1;
			}
			break;
		}
			
		Clicktime.gesture = 'n';
		Clicktime.clicktime = 0;
		if (Clicktime.location1 != 0 && Clicktime.location2 != 0) {
			LineDrawer (Clicktime.xi, Clicktime.yi, Clicktime.xf, Clicktime.yf); //Draw line
			Clicktime.location1 = 0;
			Clicktime.location2 = 0;
			Clicktime.xi = 0;
			Clicktime.xf = 0;
			Clicktime.yi = 0;
			Clicktime.yf = 0;
		}
	}
	void SpawnInductor(float i, float j, float k){
		inductor_im = GameObject.Instantiate (Inductor_im,new Vector3(i,j,k),Quaternion.identity) as GameObject;
	}
	
	void SpawnCapacitor(float i, float j, float k){
		capacitor_im = GameObject.Instantiate (Capacitor_im,new Vector3(i,j,k),Quaternion.identity) as GameObject;
	}
	
	void SpawnPower(float i, float j, float k){
		power_im = GameObject.Instantiate (Power_im,new Vector3(i,j,k),Quaternion.identity) as GameObject;
	}
	void SpawnResistor(float i, float j, float k){
		resistor_im = GameObject.Instantiate (Resistor_im,new Vector3(i,j,k),Quaternion.identity) as GameObject;
	}
	void LineDrawer(float xi, float yi, float xf, float yf){
		Vector3 v1 = new Vector3(xi,yi,0);
		Vector3 v2 = new Vector3(xf-xi, yf-yi, 0);
		Debug.DrawLine(v1,v2, Color.red);
	}

	void approximateposition(float i, float j){

		if (i > 0) {
			if (j > 0) {
				Clicktime.square = 'a';
				Clicktime.element_place_x = A.nx;
				Clicktime.element_place_y = A.ny;
				Debug.Log ("Square A");
			} else if (j < 0) {
				Clicktime.square = 'c';
				Clicktime.element_place_x = C.nx;
				Clicktime.element_place_y = C.ny;
				Debug.Log ("Square C");
			}
		} else if (i < 0) {
			if (j > 0){
				Clicktime.square = 'b';
				Clicktime.element_place_x = B.nx;
				Clicktime.element_place_y = B.ny;
				Debug.Log ("Square B");
			} else if (j < 0) {
				Clicktime.square = 'd';
				Clicktime.element_place_x = D.nx;
				Clicktime.element_place_y = D.ny;
				Debug.Log ("Square D");
		}
	}
	
}



class SampleListener : Listener
{
	
	private void SafeWriteLine (string line)
	{
		UnityEngine.Debug.Log(line);
	}

	public override void OnInit (Controller controller)
	{

	}

	public override void OnConnect (Controller controller)
	{
		//SafeWriteLine ("Connected");
		controller.EnableGesture (Gesture.GestureType.TYPE_CIRCLE);
		controller.EnableGesture (Gesture.GestureType.TYPE_SWIPE);

	}

	public override void OnDisconnect (Controller controller)
	{
	}
	
	public override void OnExit (Controller controller)
	{
	}


	public override void OnFrame (Controller controller)
	{

		// Get the most recent frame and report some basic information
		Frame frame = controller.Frame ();
		// Get gestures
		foreach (Hand hand in frame.Hands) {
		float i =0;
		float j =0;

			// Get the hand's normal vector and direction
			Vector normal = hand.PalmNormal;
			Vector direction = hand.Direction;
			i = (float)hand.PalmPosition.x ;
			Clicktime.finali = -i*40/300 + 10;
			j = (float)hand.PalmPosition.y;
			Clicktime.finalj = -40 + 40*j/150 + 10 ;

			/*if  (hand.PinchStrength > 0.7) {
				Clicktime.IsPinch = true;
				Clicktime.gesture = 'p';
				SafeWriteLine ("Pinch gesture");
			} else {
				Clicktime.IsPinch = false;
				Clicktime.gesture = 'n';
			}*/

		}

		
		GestureList gestures = frame.Gestures ();
		for (int i = 0; i < gestures.Count; i++) {
			Gesture gesture = gestures [i];
				switch (gesture.Type) {
				case Gesture.GestureType.TYPE_CIRCLE:
					CircleGesture circle = new CircleGesture (gesture);
					foreach (Hand hand in frame.Hands) {
						if (hand.IsLeft == true){
						Clicktime.gesture = 's';
						SafeWriteLine ("Circle left gesture");
						} else {
						Clicktime.gesture = 'c';
						SafeWriteLine ("Circle right gesture");
						}
				}
					break;
				case Gesture.GestureType.TYPE_SWIPE:
					SwipeGesture swipe = new SwipeGesture (gesture);
					foreach (Hand hand in frame.Hands) {
						if (hand.IsLeft == true){
							Clicktime.gesture = 'k';
							SafeWriteLine ("Swipe left gesture");
						} else {
							Clicktime.gesture = 'w';
							SafeWriteLine ("Swipe gesture");
						}
					}
					break;

					// circle left -- resistor
					//circle right -- inductor
					//swipe left -- capacitor
					//swipe right -- power

				default:
					SafeWriteLine ("  Unknown gesture type.");
					Clicktime.clicktime = 0;
					break;
			
			}
		}
		
		if (!frame.Hands.IsEmpty || !frame.Gestures ().IsEmpty) {
			SafeWriteLine ("No hands");
		}
	}
	}
}