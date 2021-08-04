
void LambdaPars() {

//proton--------------------------------------
  float Purity_p = 0.9819;
  float Sec_p = 0.1417;

  float Prim_p = 0.8569;
  float Sec_mat_p = 0.0015 ;
  float SecLam_p = 0.70 * Sec_p;
  float SecSigma_p = 0.30 * Sec_p;
  float MissId_p = 1.0 - Purity_p;

//antiproton------------------------------
  float Purity_Ap = 0.9793;
  float Sec_Ap = 0.1410;

  float Prim_Ap = 0.8589;
  float Sec_mat_Ap = 0.0001;
  float SecLam_Ap = 0.70 * Sec_Ap;
  float SecSigma_Ap = 0.30 * Sec_Ap;
  float MissId_Ap = 1.0 - Purity_Ap;

//deuteron----------------------------------
  float Purity_d = 0.8809;
  float Prim_d = 0.9762;
  float Mat_d = 0.0238;
  float MissId_d = 1.0 - Purity_d;

//antideuteron ----------------------------
  float Purity_Ad = 0.8457;
  float MissId_Ad = 1.0 - Purity_Ad;
//88888888888888888888888888888888888888888888888888888888888
  float pd = 0.0;
  float pLd = 0.0;
  float pSd = 0.0;
  float pd_m = 0.0;
  float pLd_m = 0.0;
  float pSd_m = 0.0;

  float p_md = 0.0;
  float p_md_m = 0.0;


  float pMiss_d = 0.0;
  float pLMiss_d = 0.0;
  float pSMiss_d = 0.0;
  float p_mMiss_d = 0.0;
  float Miss_pd = 0.0;
  float Miss_pd_m = 0.0;
  float Miss_pMiss_d = 0.0;

  float ApAd = 0.0;
  float ApLAd = 0.0;
  float ApSAd = 0.0;
  float Ap_mAd = 0.0;
  float Miss_ApAd = 0.0;
  float ApMiss_Ad = 0.0;
  float ApLMiss_Ad = 0.0;
  float ApSMiss_Ad = 0.0;
  float Ap_mMiss_Ad = 0.0;
  float Miss_ApMiss_Ad = 0.0;
//999999999999999999999999999999999999999999999999999999999999999999999

  std::cout << "Calculating Lambda Parameters" << std::endl;

  pd           = Purity_p * Purity_d * Prim_d * Prim_p;
  pLd          = Purity_p * Purity_d * Prim_d * SecLam_p;
  pSd          = Purity_p * Purity_d * Prim_d * SecSigma_p;
  p_md         = Purity_p * Purity_d * Prim_d * Sec_mat_p;
  Miss_pd      = Purity_d * Prim_d * MissId_p;

  pd_m         = Purity_p * Purity_d * Mat_d * Prim_p;
  pLd_m        = Purity_p * Purity_d * Mat_d * SecLam_p;
  pSd_m        = Purity_p * Purity_d * Mat_d * SecSigma_p;
  p_md_m       = Purity_p * Purity_d * Mat_d * Sec_mat_p;
  Miss_pd_m    =  Mat_d * MissId_p;

  pMiss_d      = Purity_p *  MissId_d * Prim_p;
  pLMiss_d     = Purity_p *  MissId_d * SecLam_p;
  pSMiss_d     = Purity_p *  MissId_d * SecSigma_p;
  p_mMiss_d    = Purity_p *  MissId_d * Sec_mat_p;
  Miss_pMiss_d = MissId_d * MissId_p;


  std::cout << "********************************************************* Lambda Parameters pd pairs" << std::endl;
  std::cout << "  pd              ==   " << pd << std::endl;
  std::cout << " pLd              ==   " << pLd << std::endl;
  std::cout << " pSd              ==   " << pSd << std::endl;
  std::cout << " p_md             ==   " << p_md << std::endl;
  std::cout << " pd_m             ==   " << pd_m  << std::endl;
  std::cout << " pLd_m            ==   " << pLd_m << std::endl;
  std::cout << " pSd_m            ==   " << pSd_m << std::endl;
  std::cout << " p_md_m           ==   " << p_md_m << std::endl;


  std::cout << " pMiss_d          ==   " << pMiss_d << std::endl;
  std::cout << " pLMiss_d         ==   " << pLMiss_d << std::endl;
  std::cout << " pSMiss_d         ==   " << pSMiss_d << std::endl;
  std::cout << " p_mMiss_d        ==   " << p_mMiss_d << std::endl;
  std::cout << " Miss_pd          ==   " << Miss_pd  << std::endl;
  std::cout << " Miss_pd_m        ==   " << Miss_pd_m << std::endl;
  std::cout << " Miss_pMiss_d     ==   " << Miss_pMiss_d << std::endl;

  std::cout << " Total            ==   " << pd + pLd + pSd + p_md + pd_m + pLd_m + pSd_m + p_md_m + pMiss_d + pLMiss_d + pSMiss_d + p_mMiss_d + Miss_pd + Miss_pd_m + Miss_pMiss_d << std::endl;


  ApAd           =  Purity_Ap * Purity_Ad * Prim_Ap;
  ApLAd          =  Purity_Ap * Purity_Ad * SecLam_Ap;
  ApSAd          =  Purity_Ap * Purity_Ad * SecSigma_Ap;
  Ap_mAd         =  Purity_Ap * Purity_Ad * Sec_mat_Ap;
  Miss_ApAd      =  Purity_Ad * MissId_p;

  ApMiss_Ad      =  Purity_Ap  *  MissId_Ad * Prim_Ap;
  ApLMiss_Ad     =  Purity_Ap  *  MissId_Ad * SecLam_Ap;
  ApSMiss_Ad     =  Purity_Ap  *  MissId_Ad * SecSigma_Ap;
  Ap_mMiss_Ad    =  Purity_Ap  *  MissId_Ad * Sec_mat_Ap;
  Miss_ApMiss_Ad =  MissId_p   *  MissId_Ad;

  std::cout << "********************************************************* Lambda Parameters ApAd pairs" << std::endl;

  std::cout << "  ApAd                  ==   " << ApAd << std::endl;
  std::cout << "  ApLAd                 ==   " << ApLAd << std::endl;
  std::cout << "  ApSAd                 ==   " << ApSAd << std::endl;
  std::cout << "  Ap_mAd                ==   " << Ap_mAd << std::endl;
  std::cout << "  ApMiss_Ad             ==   " << ApMiss_Ad << std::endl;
  std::cout << "  ApLMiss_Ad            ==   " << ApLMiss_Ad << std::endl;
  std::cout << "  ApSMiss_Ad            ==   " << ApSMiss_Ad << std::endl;
  std::cout << "  Ap_mMiss_Ad           ==   " << Ap_mMiss_Ad << std::endl;
  std::cout << "  Miss_ApAd             ==   " << Miss_ApAd << std::endl;
  std::cout << "  Miss_ApMiss_Ad        ==   " << Miss_ApMiss_Ad << std::endl;
  std::cout << " Total                  ==   " << ApAd + ApLAd + ApSAd + Ap_mAd + ApMiss_Ad + ApLMiss_Ad + ApSMiss_Ad + Ap_mMiss_Ad + Miss_ApAd + Miss_ApMiss_Ad << std::endl;
}




