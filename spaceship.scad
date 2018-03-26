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
}
}