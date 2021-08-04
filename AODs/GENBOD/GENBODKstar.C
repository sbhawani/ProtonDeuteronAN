float GetkStar(const TLorentzVector &Part1Momentum,
               const TLorentzVector &Part2Momentum) {
  static float results = 0.;
  static TLorentzVector SPtrack, TPProng, trackSum, SPtrackCMS, TPProngCMS;
  SPtrack.SetXYZM(Part1Momentum.X(), Part1Momentum.Y(), Part1Momentum.Z(),
                  Part1Momentum.M());
  TPProng.SetXYZM(Part2Momentum.X(), Part2Momentum.Y(), Part2Momentum.Z(),
                  Part2Momentum.M());
  trackSum =  SPtrack +TPProng;
  float beta = trackSum.Beta();
  float betax = beta * cos(trackSum.Phi()) * sin(trackSum.Theta());
  float betay = beta * sin(trackSum.Phi()) * sin(trackSum.Theta());
  float betaz = beta * cos(trackSum.Theta());

  SPtrackCMS = SPtrack;
  TPProngCMS = TPProng;

  SPtrackCMS.Boost(-betax, -betay, -betaz);
  TPProngCMS.Boost(-betax, -betay, -betaz);

  static TLorentzVector trackRelK;

  trackRelK = SPtrackCMS - TPProngCMS;
  results = 0.5 * trackRelK.P();
  return results*1000;  // in MeV
}

float GetkStarPrim(const TLorentzVector &Part1Momentum,
               const TLorentzVector &Part2Momentum) {
  static float results = 0.;
  static TLorentzVector SPtrack, TPProng, trackSum, SPtrackCMS, TPProngCMS;
  SPtrack.SetXYZM(Part1Momentum.X(), Part1Momentum.Y(), Part1Momentum.Z(),
                  Part1Momentum.M());
  TPProng.SetXYZM(Part2Momentum.X(), Part2Momentum.Y(), Part2Momentum.Z(),
                  1.875);
  trackSum =  SPtrack +TPProng;
  float beta = trackSum.Beta();
  float betax = beta * cos(trackSum.Phi()) * sin(trackSum.Theta());
  float betay = beta * sin(trackSum.Phi()) * sin(trackSum.Theta());
  float betaz = beta * cos(trackSum.Theta());

  SPtrackCMS = SPtrack;
  TPProngCMS = TPProng;

  SPtrackCMS.Boost(-betax, -betay, -betaz);
  TPProngCMS.Boost(-betax, -betay, -betaz);

  static TLorentzVector trackRelK;

  trackRelK = SPtrackCMS - TPProngCMS;
  results = 0.5 * trackRelK.P();
  return results*1000;  // in MeV
}




float GetInMassDelta(const TLorentzVector &Part1Momentum,
               const TLorentzVector &Part2Momentum) {
  static float results = 0.;
  static TLorentzVector SPtrack, TPProng, trackSum, SPtrackCMS, TPProngCMS;
  SPtrack.SetXYZM(Part1Momentum.X(), Part1Momentum.Y(), Part1Momentum.Z(),
                  Part1Momentum.M());
  TPProng.SetXYZM(Part2Momentum.X(), Part2Momentum.Y(), Part2Momentum.Z(),
                  Part2Momentum.M());
  trackSum =  SPtrack +TPProng;
//cout << Part1Momentum.M()<<endl;
//cout << Part2Momentum.M()<<endl;
  float beta = trackSum.Beta();
  float betax = beta * cos(trackSum.Phi()) * sin(trackSum.Theta());
  float betay = beta * sin(trackSum.Phi()) * sin(trackSum.Theta());
  float betaz = beta * cos(trackSum.Theta());

  SPtrackCMS = SPtrack;
  TPProngCMS = TPProng;

  SPtrackCMS.Boost(-betax, -betay, -betaz);
  TPProngCMS.Boost(-betax, -betay, -betaz);

  static TLorentzVector trackRelK,trackMass;

  trackRelK = SPtrackCMS - TPProngCMS;
  trackMass = SPtrackCMS + TPProngCMS;
  cout<< trackMass.M()<<endl;
  results = 0.5 * trackRelK.P();
  return results*1000;  // in MeV
}

void GENBODKstar() {
  TString FileName = "/home/sbhawani/cernbox/ProtonDeuteron/Outputs/CATSOutput/DecayMatrices/DeltaDecayCorrect1.root";

  TFile *outputfile = new TFile(FileName,"update");
  if(!outputfile) outputfile = new TFile(FileName,"recreate");


  TRandom3 rangen;
  const double MomMean = 3.0;   // some assumption
  const double MomSpread = 0.5; // some assumption

  const double MomMeanProton = 0.0;   // some assumption
  const double MomSpreadProton = 0.3; // some assumption

  const double MomMeanPion = 0.0;   // some assumption
  const double MomSpreadPion = 0.3; // some assumption
  const double MassDeuteron = 1.875;
  //const double MassPion = TDatabasePDG::Instance()->GetParticle(211)->Mass();

  const double MassDelta = TDatabasePDG::Instance()->GetParticle(2224)->Mass(); // Delta++
  cout<<"reached -1"<<endl;
  TLorentzVector trueDelta, PionDeltaChild, ProtonDeltaChild, Vproton, Vpion;
  TGenPhaseSpace event;
  double deltaDecay[2] = { TDatabasePDG::Instance()->GetParticle(2212)->Mass(), TDatabasePDG::Instance()->GetParticle(211)->Mass()};  // decay to proton (2212) and pion (211)
  cout<<"reached -2"<<endl;
  auto histDecay = new TH2F("hRes_dp_ppi", "; k* (MeV/c); entries", 1000, 0, 1000,1000, 0, 1000);
  auto hMomPionChild = new TH1F("hMomPionChild", "; p (GeV/c); entries", 100, 0, 5);
  auto hMomProtonChild = new TH1F("hMomProtonChild", "; p (GeV/c); entries", 100, 0, 5);
  auto hkstarPiproton = new TH1F("hkstarPiproton", "; k* (MeV/c); entries", 5000, 0, 5000);
  auto hkstarPrimPiproton = new TH1F("hkstarPrimPiproton", "; k*' (MeV/c); entries", 5000, 0, 5000);
  for (int i = 0; i < 100000000; ++i) {

    trueDelta.SetXYZM(rangen.Gaus(MomMean,MomSpread),rangen.Gaus(MomMean,MomSpread),rangen.Gaus(MomMean,MomSpread), MassDelta);

        // force decay to proton + pion
        event.SetDecay(trueDelta, 2, deltaDecay);
        event.Generate();
        // compute k* of proton and pion
        ProtonDeltaChild = *(event.GetDecay(0));
        PionDeltaChild = *(event.GetDecay(1));

   Vproton.SetXYZM(rangen.Gaus(MomMeanProton,MomSpreadProton),rangen.Gaus(MomMeanProton,MomSpreadProton),rangen.Gaus(MomMeanProton,MomSpreadProton), TDatabasePDG::Instance()->GetParticle(2212)->Mass());
   Vpion.SetXYZM(rangen.Gaus(MomMeanPion,MomSpreadPion),rangen.Gaus(MomMeanPion,MomSpreadPion),rangen.Gaus(MomMeanPion,MomSpreadPion), TDatabasePDG::Instance()->GetParticle(211)->Mass());
   //histDecay->Fill(GetkStar(ProtonDeltaChild, PionDeltaChild),GetkStarPrim(ProtonDeltaChild, PionDeltaChild));
   histDecay->Fill(GetkStar(Vproton, Vpion),GetkStarPrim(Vproton, Vpion));
//cout<< GetkStar(Vproton, Vpion)<<GetkStarPrim(Vproton, Vpion)<<endl;
  // hMomPionChild->Fill(PionDeltaChild.P());
 //  hMomProtonChild->Fill(ProtonDeltaChild.P());
 //  hkstarPiproton->Fill(GetkStar(ProtonDeltaChild, PionDeltaChild));
 //  hkstarPrimPiproton->Fill(GetkStarPrim(ProtonDeltaChild, PionDeltaChild));
  }

  auto c = new TCanvas();
  histDecay->Draw("colz");
  hMomPionChild->Draw("");
  hMomProtonChild->Draw("");
  hkstarPiproton->Draw("");
  hkstarPrimPiproton->Draw("");
  outputfile->cd();

  histDecay->Write("",TObject::kOverwrite);
  hMomPionChild->Write("",TObject::kOverwrite);
  hMomProtonChild->Write("",TObject::kOverwrite);
  hkstarPiproton->Write("",TObject::kOverwrite);
  hkstarPrimPiproton->Write("",TObject::kOverwrite);
  delete histDecay;
  delete outputfile;

}
