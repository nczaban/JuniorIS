scale([2,2,2]){

union(){
// Diamond
	union(){
	difference(){
	translate([0,-2.5,0]) rotate(45, [0,1,0]) cube([3.5, 0.3, 3.5], center=true);
	translate([0,-2.5,0]) rotate(45, [0,1,0]) cube([3.4, 0.3, 3.4], center=true);
	}
	}

// Cross
	difference(){
	union(){
	translate([0,2.5,0]) cube([5, 0.3, 2.5], center=true);
	translate([0,2.5,0]) cube([2.5, 0.3, 5], center=true);
	}
	union(){
	translate([0,2.5,0]) cube([4.9, 0.3, 2.4], center=true);
	translate([0,2.5,0]) cube([2.4, 0.3, 4.9], center=true);
	}
	}

// Star
	difference(){
	union(){
	intersection(){
	translate([0,1.1,2.5]) rotate(90, [1,0,0]) cylinder(h=2.5, r1=0.1,r2=1.5, $fn=50, center=true);
	translate([0,0,2.5]) cube([5, 5, 0.3], center=true);
	}
	
	intersection(){
	translate([0,-1.1,2.5]) rotate(-90, [1,0,0]) cylinder(h=2.5, r1=0.1, r2=1.5, $fn=50, center=true);
	translate([0,0,2.5]) cube([5, 5, 0.3], center=true);
	}
	
	intersection(){
	translate([-1.1,0,2.5]) rotate(90, [0,1,0]) cylinder(h=2.5, r1=0.1, r2=1.5, $fn=50, center=true);
	translate([0,0,2.5]) cube([5, 5, 0.3], center=true);
	}
	
	intersection(){
	translate([1.1,0,2.5]) rotate(-90, [0,1,0]) cylinder(h=2.5, r1=0.1, r2=1.5, $fn=50, center=true);
	translate([0,0,2.5]) cube([5, 5, 0.3], center=true);
	}
	}
	
	// Interior segment to remove
	union(){
	intersection(){
	translate([0,1.1,2.5]) rotate(90, [1,0,0]) cylinder(h=2.45, r1=0.01, r2=1.4, $fn=50, center=true);
	translate([0,0,2.5]) cube([5, 5, 0.3], center=true);
	}
	intersection(){
	translate([0,-1.1,2.5]) rotate(-90, [1,0,0]) cylinder(h=2.45, r1=0.01, r2=1.4, $fn=50, center=true);
	translate([0,0,2.5]) cube([5, 5, 0.3], center=true);
	}
	intersection(){
	translate([-1.1,0,2.5]) rotate(90, [0,1,0]) cylinder(h=2.45, r1=0.01, r2=1.4, $fn=50, center=true);
	translate([0,0,2.5]) cube([5, 5, 0.3], center=true);
	}
	intersection(){
	translate([1.1,0,2.5]) rotate(-90, [0,1,0]) cylinder(h=2.45, r1=0.01, r2=1.4, $fn=50, center=true);
	translate([0,0,2.5]) cube([5, 5, 0.3], center=true);
	}
	}
	}
	
// Spade
	difference(){
	union(){
	intersection(){
	translate([2.5,0,1.1]) rotate(180, [0,1,0]) cylinder(h=2.8, r1=0.1, r2=2.3, $fn=50, center=true);
	translate([2.5,0,0]) cube([0.3,5,5], center=true);
	}
	translate([2.5,1.3,-0.6]) rotate(90, [0,1,0]) cylinder(h=0.3, r1=1, r2=1, $fn=50, center=true);
	translate([2.5,-1.3,-0.6]) rotate(90, [0,1,0]) cylinder(h=0.3, r1=1, r2=1, $fn=50, center=true);
	translate([2.5,0,-0.5]) cube([0.3, 1, 4], center=true);
	}
	union(){
	intersection(){
	translate([2.5,0,1.1]) rotate(180, [0,1,0]) cylinder(h=2.8, r1=0, r2=2.2, $fn=50, center=true);
	translate([2.5,0,0]) cube([0.3,5,5], center=true);
	}
	translate([2.5,1.3,-0.65]) rotate(90, [0,1,0]) cylinder(h=0.3, r1=.95, r2=.95, $fn=50, center=true);
	translate([2.5,-1.3,-0.65]) rotate(90, [0,1,0]) cylinder(h=0.3, r1=.95, r2=.95, $fn=50, center=true);
	translate([2.5,0,-0.5]) cube([0.3, .9, 3.9], center=true);
	}
	}
	
// Heart
	difference(){
	union(){
	translate([1.4,1.2,-2.5]) cylinder(h=0.3, r1=1.2, r2=1.2, $fn=50, center=true);
	translate([1.4,-1.2,-2.5]) cylinder(h=0.3, r1=1.2, r2=1.2, $fn=50, center=true);
	intersection(){
	translate([-1,0,-2.5]) rotate(90, [0,1,0]) cylinder(h=3, r1=0.1, r2=2, $fn=50, center=true);
	translate([0,0,-2.5]) cube([5,5,0.3], center=true);
	}
	}
	union(){
	translate([1.4,1.2,-2.5]) cylinder(h=0.3, r1=1.1, r2=1.1, $fn=50, center=true);
	translate([1.4,-1.2,-2.5]) cylinder(h=0.3, r1=1.1, r2=1.1, $fn=50, center=true);
	intersection(){
	translate([-1,0,-2.5]) rotate(90, [0,1,0]) cylinder(h=3, r1=0, r2=1.9, $fn=50, center=true);
	translate([0,0,-2.5]) cube([5,5,0.3], center=true);
	}
	translate([.9,0,-2.5]) cube([1,1.2,0.3], center=true);

	}
	}
	
// Club
	difference(){
	union(){
	translate([-2.5, 0, 1.25]) rotate(90, [0,1,0]) cylinder(h=0.3, r1=1.25, r2=1.25, $fn=50, center=true);
	translate([-2.5, -1, -.25]) rotate(90, [0,1,0]) cylinder(h=0.3, r1=1.25, r2=1.25, $fn=50, center=true);
	translate([-2.5, 1, -.25]) rotate(90, [0,1,0]) cylinder(h=0.3, r1=1.25, r2=1.25, $fn=50, center=true);
	translate([-2.5, 0, -1.5]) cube([0.3,1,2], center=true);
	}
	union(){
	translate([-2.5, 0, 1.25]) rotate(90, [0,1,0]) cylinder(h=0.3, r1=1.1, r2=1.1, $fn=50, center=true);
	translate([-2.5, -1, -.25]) rotate(90, [0,1,0]) cylinder(h=0.3, r1=1.1, r2=1.1, $fn=50, center=true);
	translate([-2.5, 1, -.25]) rotate(90, [0,1,0]) cylinder(h=0.3, r1=1.1, r2=1.1, $fn=50, center=true);
	translate([-2.5, 0, -1.5]) cube([0.3,.9,1.9], center=true);
	}
	}
}
}