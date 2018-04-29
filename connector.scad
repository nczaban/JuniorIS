difference(){
intersection(){
	cube(6, center=true);
	sphere(4, $fn=50);
}
cylinder(h=6, r1=1.5, r2=1.5, $fn=50, center=true);
rotate(90, [1,0,0]) cylinder(h=6, r1=1.5, r2=1.5, $fn=50, center=true);
rotate(90, [0,1,0]) cylinder(h=6, r1=1.5, r2=1.5, $fn=50, center=true);
}