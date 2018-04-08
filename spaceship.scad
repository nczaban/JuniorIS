// Spaceship
rotate(90, [0,0,1]) rotate(-90, [0,1,0]){
union(){
	translate([-1.5,0.5,0]) rotate(90,[0,1,0]) cylinder(.25, .25, .25, $fn=50, true);
	translate([-1.5,-0.5,0]) rotate(90,[0,1,0]) cylinder(.25, .25, .25, $fn=50, true);
intersection()
{
	cube([7,4,1], center=true);
	rotate(90,[0,1,0]) cylinder(3, 1, 0, true);
}
intersection()
{
	translate([-0.5,1.5,0.25]) rotate(100, [1,-0.2,0]) cylinder(r1=0.1, r2=0.4, h=2, $fn=50, true);
	translate([-0.6,1.25,0.2]) rotate(100, [1,-0.2,0]) cube([0.8,0.1,1.5], true);
}
}
}