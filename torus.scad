//Taurus
union(){
for(i=[1:1:360]){
	rotate(i, [0,1,0]) translate([10, 0, 0]) cylinder(2, 4, 4, $fn=25);
}
}