// Asteroid

intersection(){
	cube(7, center=true);
	rotate(45, [1,1,1]) cube(7, center=true);
	rotate(-45, [1,1,1]) cube(7, center=true);
	rotate(45, [1,-1,1]) cube(7, center=true);
	rotate(-45, [1,-1,1]) cube(7, center=true);
	rotate(45, [-1,1,1]) cube(7, center=true);
	rotate(-45, [-1,1,1]) cube(7, center=true);
	rotate(45, [1,-1,-1]) cube(7, center=true);
	rotate(-45, [1,-1,-1]) cube(7, center=true);
}