import matplotlib.pyplot as plt

Nsizes = [32,64,128,256,512,1024,2048,4096,8192]
Theoretical = [6.84463e-05, 0.000549726, 0.00440643, 0.035286, 0.282426, 2.25996, 18.0819, 144.664, 1157.35]
NaiveResults = [0.000223,0.001749, 0.017780, 0.142042, 1.388570, 24.969940, 254.911866, 2233.643528, 18600.950484]
Opt1Results = [0.000186, 0.001451, 0.011352, 0.091328, 0.708196, 5.667843, 45.265446, 362.500027, 2914.189976]
Opt2Results = [0.000194, 0.001511, 0.013084, 0.093948, 0.742125, 5.950698, 47.896635, 391.200087, 3304.406717]
Opt2_64Results = [0.000, 0.001451, 0.012878, 0.096684, 0.751683, 6.097923, 49.376596, 393.352007, 3192.598471]
Opt3Results = [0.000461, 0.003732, 0.031031, 0.237299, 1.891817, 15.196035, 122.090300, 973.819655, 7894.428863]

# plt.plot(Nsizes, Theoretical, label = 'Theoretical', marker='o', markersize = 2)
# plt.plot(Nsizes, NaiveResults, label = 'Naive', marker='o', markersize = 2)
# plt.plot(Nsizes, Opt1Results, label = 'Opt-1', marker='o', markersize = 2)
# plt.plot(Nsizes, Opt2Results, label = 'Opt-2, s=32', marker='o', markersize = 2)
# plt.plot(Nsizes, Opt2_64Results, label = 'Opt-2, s=64', marker='o', markersize = 2)
# plt.plot(Nsizes, Opt3Results, label = 'Opt-3', marker='o', markersize = 2)
# plt.yscale('log')
# plt.xscale('log')
# plt.xlabel('log(n)')
# # plt.xlabel('N')
# plt.ylabel('log(Time Taken)')
# plt.legend()
# plt.savefig('Log(Time)-vs-Log(N)-Graph')
# # plt.show()

x = [1,2,3,4,5,6]
my_xticks = ['Theoretical', 'Naive', 'Opt-1', 'OPt-2, s=32', 'Opt-2, s=64', 'Opt-3']
plt.xticks(x, my_xticks)
for ct, size in enumerate(Nsizes):
	y = [Theoretical[ct], NaiveResults[ct], Opt1Results[ct], Opt2Results[ct], Opt2_64Results[ct], Opt3Results[ct]]
	plt.plot(x,y,label = size, marker='o', markersize=2)
plt.yscale('log')
plt.ylabel('Log ( Time Taken for different n )')
plt.legend()
# plt.show()
plt.savefig('Log(Time)-vs-Algos-Graph')