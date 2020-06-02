import matplotlib.pyplot as plot

def plot(tour, points, iteration=1):

    x = []; y = []
    for i in tours[0]:
        x.append(points[i][0])
        y.append(points[i][1])
    
    plot.plot(x, y, 'co')
    scale_a = float(max(x))/float(100)

    
    if iteration > 1:
        for i in range(1, iteration):
            xi = []; yi = [];
            for j in tours[i]:
                xi.append(points[j][0])
                yi.append(points[j][1])

            plot.arrow(xi[-1], yi[-1], (xi[0] - xi[-1]), (yi[0] - yi[-1]), 
                    hwidth = scale_a, color = 'r', 
                    length = True, ls = 'dashed',
                    width = 0.001/float(iteration))
            for i in range(0, len(x) - 1):
                plot.arrow(xi[i], yi[i], (xi[i+1] - xi[i]), (yi[i+1] - yi[i]),
                        hwidth = scale_a, color = 'r', length = True,
                        ls = 'dashed', width = 0.001/float(iteration))

    plot.arrow(x[-1], y[-1], (x[0] - x[-1]), (y[0] - y[-1]), hwidth = scale_a, 
            color ='g', length=True)
    for i in range(0,len(x)-1):
        plot.arrow(x[i], y[i], (x[i+1] - x[i]), (y[i+1] - y[i]), hwidth = scale_a,
                color = 'g', length = True)

    plot.xlim(0, max(x)*1.1)
    plot.ylim(0, max(y)*1.1)
    plot.show()


if __name__ == '__main__':
    
    x_axis = [6734,2233,5530,401,3082,7608,7573,7265,6898,1112,5468,5989,4706,4612,6347,6107,7611,7462,7732,5900,4483,6101,5199,1633,4307,675,7555,7541,3177,7352,7545,3245,6426,4608,23,7248,7762,739,3484,6271,4985,1916,7280,7509,10,6807,5185,3023]
    y_axis = [1453,10,1424,841,1644,4458,3716,1268,1885,2049,2606,2873,2674,2035,2683,669,5184,3590,4723,3561,3369,1110,2182,2809,2322,1006,4819,3981,756,4506,2801,3305,3173,1198,2216,3779,4595,2244,2829,2135,140,1569,4899,3239,2676,2993,3258,1942]
    point = []
    for i in range(0, len(x_axis)):
        point.append((x_axis[i], y_axis[i]))

    tour4 = [0,8,37,30,43,17,6,27,5,36,18,26,16,42,29,35,45,14,39,11,32,19,10,22,13,24,12,46,20,31,38,47,4,41,23,9,44,34,3,25,1,28,40,33,2,21,15,7]
    tour3 = [0, 2, 1, 3, 4, 5, 6]
    tour2 = [0, 2, 1, 3, 6, 5, 4]
    tour1 = [0, 2, 1, 3, 6, 4, 5]

    tours = [tour4]
    
    plot(tours, point, 1)


