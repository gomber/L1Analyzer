'''
Usage:python jetEfficiencyPlot.py RootFile.root label[optional]

Script to make some quick efficiency plots for MET to test stage 2 trigger performance.


Author: Usama Hussain, UW Madison
Cite: L.Dodd L1 JetEfficiency code

'''

from subprocess import Popen
from sys import argv, exit, stdout, stderr

import ROOT

# So things don't look like crap.
ROOT.gROOT.SetStyle("Plain")
ROOT.gROOT.SetBatch(True)
ROOT.gStyle.SetOptStat(0)

######## File #########
if len(argv) < 2:
   print 'Usage:python jetEfficiencyPlot.py RootFile.root RootFile_new.root label[optional]'
   exit()

infile = argv[1]
ntuple_file = ROOT.TFile(infile)

######## LABEL & SAVE WHERE #########

if len(argv)>2:
   saveWhere='~/www/'+argv[3]+'_'
else:
   saveWhere='MetEfficiencyPlots/Eff_'



####### Calibration factor ####
L1_CALIB_FACTOR = 1.0
L1G_CALIB_FACTOR = 1.0


#####################################
#Get met Eff NTUPLE                 #
#####################################


#jet_ntuple = ntuple_file.Get("corrjetEfficiency/Ntuple")
met_ntuple = ntuple_file.Get("JetRecoTree")
#met_ntuple1 = ntuple_file.Get("l1UpgradeEmuTree/L1UpgradeTree")
canvas = ROOT.TCanvas("asdf", "adsf", 800, 800)

def make_plot(tree, variable, selection, binning, xaxis='', title=''):
    ''' Plot a variable using draw and return the histogram '''
    draw_string = "%s>>htemp(%s)" % (variable, ", ".join(str(x) for x in binning))
    tree.Draw(draw_string, selection, "goff")
    output_histo = ROOT.gDirectory.Get("htemp").Clone()
#    output_histo.GetXaxis().SetTitle(xaxis)
#    output_histo.GetYaxis().SetTitle("Efficiency")
    output_histo.SetTitle(title)
    return output_histo


def make_l1g_efficiency(denom, num,markercolor,linecolor):
    ''' Make an efficiency graph with the "UCT" style '''
    eff = ROOT.TGraphAsymmErrors(num, denom)
    eff.SetMarkerStyle(22)
    eff.SetMarkerColor(markercolor)
    eff.SetMarkerSize(1.2)
    eff.SetLineColor(linecolor)
    return eff


def compare_efficiencies(ntuple,variable, l1MetCut, binning, filename,
                         title='', xaxis='',showL1=False):
    ''' Returns a (L1, L1G) tuple of TGraphAsymmErrors '''
    denom = make_plot(
        ntuple, variable,
        "", # No selection
        binning,
    )
    num_l1g_1 = make_plot(
        ntuple, variable,
        "metSum>60",
        binning
    )
    num_l1g_2 = make_plot(
        ntuple, variable,
        "metSum>70",
        binning
    )
    num_l1g_3 = make_plot(
        ntuple, variable,
        "metSum>80",
        binning
    )
    num_l1g_4 = make_plot(
        ntuple, variable,
        "metSum>90",
        binning
    )
    num_l1g_5 = make_plot(
        ntuple, variable,
        "metSum>100",
        binning
    )
    frame = ROOT.TH1F("frame", "", *binning)
    l1g_1 = make_l1g_efficiency(denom, num_l1g_1,ROOT.kGreen,ROOT.kBlack)
    l1g_2 = make_l1g_efficiency(denom, num_l1g_2,ROOT.kBlue,ROOT.kBlack)
    l1g_3 = make_l1g_efficiency(denom, num_l1g_3,ROOT.kRed,ROOT.kBlack)
    l1g_4 = make_l1g_efficiency(denom, num_l1g_4,ROOT.kAzure,ROOT.kBlack)
    l1g_5 = make_l1g_efficiency(denom, num_l1g_5,ROOT.kViolet,ROOT.kBlack)
    frame.SetMaximum(1.20)
    frame.SetMinimum(0.40)
    frame.GetYaxis().SetLabelFont(42);
    frame.GetYaxis().SetLabelSize(0.025);
    frame.GetYaxis().SetTitleSize(0.03);
    frame.GetYaxis().SetTitleFont(42);
    frame.GetXaxis().SetLabelFont(42);
    frame.GetXaxis().SetLabelSize(0.025);
    frame.GetXaxis().SetTitleSize(0.03);
    frame.GetXaxis().SetTitleFont(42);
    #frame.SetTitle(title)
    frame.GetXaxis().SetTitle(xaxis)
    frame.GetYaxis().SetTitle("Efficiency")
    frame.Draw()
    l1g_1.Draw('pe')
    l1g_2.Draw('pe')
    l1g_3.Draw('pe')
    l1g_4.Draw('pe')
    l1g_5.Draw('pe')
    legend = ROOT.TLegend(0.11,0.75,0.56,0.90,'','brNDC')
    legend.SetFillColor(ROOT.kWhite)
    legend.SetBorderSize(0)
    legend.SetLineColor(1)
    legend.SetLineStyle(2)
    legend.SetFillStyle(0)
    legend.SetTextFont(42)
    legend.AddEntry(l1g_1, "L1 MET > 60 GeV", "pe")
    legend.AddEntry(l1g_2, "L1 MET > 70 GeV", "pe")
    legend.AddEntry(l1g_3, "L1 MET > 80 GeV", "pe")
    legend.AddEntry(l1g_4, "L1 MET > 90 GeV", "pe")
    legend.AddEntry(l1g_5, "L1 MET > 100 GeV", "pe")
    legend.Draw()
   # legend2.Draw()
   # legend3.Draw()
 #   legend4.Draw()
#    legend5.Draw()
    saveas = saveWhere+filename+'.png'
    print saveas
    canvas.SaveAs(saveas)

################################################################################
# met efficiency for a cut on metPhi
################################################################################

compare_efficiencies(met_ntuple,'met',0, [50, 0, 1000],
                    'met_comparison',
                     "theMet.et", "PFMET [GeV]")
#compare_efficiencies(met_ntuple,'sumEt', 0, [50, 0, 4000],
#                   'sumEt',
#                    "theMet.sumEt", "sumEt (GeV)")

