float GetkStar(const TLorentzVector &Part1Momentum,
               const TLorentzVector &Part2Momentum) {
  static float results = 0.;
  static TLorentzVector SPtrack, TPProng, trackSum, SPtrackCMS, TPProngCMS;
  SPtrack.SetXYZM(Part1Momentum.X(), Part1Momentum.Y(), Part1Momentum.Z(),
                  Part1Momentum.M());
  TPProng.SetXYZM(Part2Momentum.X(), Part2Momentum.Y(), Part2Momentum.Z(),
                  1.875);
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

  static TLorentzVector trackRelK;

  trackRelK = SPtrackCMS - TPProngCMS;
  cout<< trackRelK.M()<<endl;
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

/*float GetInVMass(const TLorentzVector &Part1Momentum,
                        const TLorentzVector &Part2Momentum) {
      TVector3 momPart1 = Part1Momentum.GetMomentum();
      TVector3 momPart2 = Part2Momentum.GetMomentum();
      TLorentzVector trackPos, trackNeg;
      trackPos.SetXYZM(momPart1.Px(), momPart1.Py(), momPart1.Pz(),
                       part1.GetInvMass());
      trackNeg.SetXYZM(momPart2.Px(), momPart2.Py(), momPart2.Pz(),
                       part2.GetInvMass());
      TLorentzVector trackSum = trackPos + trackNeg;

      reutrn trackSum.M();
}

float GetInMassDelta(const TLorentzVector &Part1Momentum,
                        const TLorentzVector &Part2Momentum) {
      TVector3 momPart1 = Part1Momentum.GetMomentum();
      TVector3 momPart2 = Part2Momentum.GetMomentum();
      TLorentzVector trackPos, trackNeg;
      trackPos.SetXYZM(momPart1.Px(), momPart1.Py(), momPart1.Pz(),
                       part1.GetInvMass());
      trackNeg.SetXYZM(momPart2.Px(), momPart2.Py(), momPart2.Pz(),
                       part2.GetInvMass());
      TLorentzVector trackSum = trackPos + trackNeg;

      reutrn trackSum.M();
}

*/


void GENBOD() {
  TRandom3 rangen;
  const double MomMean = 1.8;   // some assumption
  const double MomSpread = 0.1; // some assumption

  const double MomMeanProton = 1.0;   // some assumption
  const double MomSpreadProton = 0.3; // some assumption

  const double MomMeanPion = 2.9;   // some assumption
  const double MomSpreadPion = 0.4; // some assumption


  const double MassDelta = TDatabasePDG::Instance()->GetParticle(2224)->Mass(); // Delta++
  cout<<"reached -1"<<endl;
  TLorentzVector trueDelta, PionDeltaChild, ProtonDeltaChild, PionDeltaChild1, ProtonDeltaChild2;
  TGenPhaseSpace event;
  double deltaDecay[2] = { TDatabasePDG::Instance()->GetParticle(2212)->Mass(), TDatabasePDG::Instance()->GetParticle(211)->Mass()};  // decay to proton (2212) and pion (211)
  cout<<"reached -2"<<endl;
  auto histDecay = new TH1F("histDecay", "; k* (MeV/c); entries", 1000, 0, 1000);

  for (int i = 0; i < 6000; ++i) {

    // randomly generate particle with Delta++ mass
    trueDelta.SetXYZM(rangen.Gaus(MomMean,MomSpread),rangen.Gaus(MomMean,MomSpread),rangen.Gaus(MomMean,MomSpread), MassDelta);

    // force decay to proton + pion
    event.SetDecay(trueDelta, 2, deltaDecay);

    event.Generate();

    // compute k* of proton and pion
    ProtonDeltaChild = *(event.GetDecay(0));

    PionDeltaChild = *(event.GetDecay(1));



    PionDeltaChild1.SetXYZM(rangen.Gaus(MomMeanProton,MomSpreadProton),rangen.Gaus(MomMeanProton,MomSpreadProton),rangen.Gaus(MomMeanProton,MomSpreadProton), TDatabasePDG::Instance()->GetParticle(2212)->Mass());
    ProtonDeltaChild2.SetXYZM(rangen.Gaus(MomMeanPion,MomSpreadPion),rangen.Gaus(MomMeanPion,MomSpreadPion),rangen.Gaus(MomMeanPion,MomSpreadPion), TDatabasePDG::Instance()->GetParticle(211)->Mass());
    histDecay->Fill(GetInMassDelta(PionDeltaChild1, ProtonDeltaChild2));
   // histDecay->Fill(GetInMassDelta(ProtonDeltaChild1, PionDeltaChild2));


  }

  auto c = new TCanvas();
  histDecay->Draw();
}
