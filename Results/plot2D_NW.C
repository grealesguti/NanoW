void plot2D_NW() {
    // Create a canvas for displaying the plots
    TCanvas *c1 = new TCanvas();

    // Open the ROOT file
    TFile *file = TFile::Open("testXY7.root");

    // Get the tree from the ROOT file
    TTree *tree = (TTree*)file->Get("Event");

    // Define variables to hold the data
    Double_t EnergyDeposit, GunX, GunY;

    // Set the branch addresses to the variables
    tree->SetBranchAddress("EnergyDeposit", &EnergyDeposit);
    tree->SetBranchAddress("GunX", &GunX);
    tree->SetBranchAddress("GunY", &GunY);

    // Create the first 2D histogram: GunX vs GunY
    TH2F *hist1 = new TH2F("hist1", "GunX vs GunY", 100, -25, 25, 100, -25, 25);
    hist1->SetStats(0);

    // Create the second 2D histogram: EnergyDeposit vs GunY
    TH2F *hist2 = new TH2F("hist2", "EnergyDeposit vs GunY", 100, -5, 5, 100, 0, 10);
    hist2->SetStats(0);

    // Get the number of entries in the tree
    Long64_t nEntries = tree->GetEntries();

    // Loop over the tree and fill the histograms
    for (Long64_t i = 0; i < nEntries; ++i) {
        tree->GetEntry(i);

        // Convert GunX, GunY, and EnergyDeposit to doubles before filling
        double dGunX = static_cast<double>(GunX)*1000;
        double dGunY = static_cast<double>(GunY)*1000;
        double dEnergyDeposit = static_cast<double>(EnergyDeposit)*1e6;

        // Fill histograms with GunX and GunY data
        if(dEnergyDeposit > 0){
            hist1->Fill(dGunX , dGunY );
        }       // GunX in mm, EnergyDeposit in microjoules

        if (i < 10) {
            std::cout << "Entry " << i << ": "
                      << "EnergyDeposit = " << dEnergyDeposit << ", "
                      << "GunX = " << dGunX << ", "
                      << "GunY = " << dGunY << std::endl;
        }
    }

    std::cout << "Number of entries in hist1: " << hist1->GetEntries() << std::endl;
    std::cout << "GunX min: " << hist1->GetXaxis()->GetXmin() << ", GunX max: " << hist1->GetXaxis()->GetXmax() << std::endl;
    std::cout << "GunY min: " << hist1->GetYaxis()->GetXmin() << ", GunY max: " << hist1->GetYaxis()->GetXmax() << std::endl;

    // Draw the first histogram: GunX vs GunY
//    c1->Clear();  // Clear the canvas
    hist1->Draw("colz");

    // Explicitly update the canvas
    c1->Update();

    // Save the plot as a PNG file
 //   hist1->SaveAs("energyDeposit_vs_GunX.png");

    // Close the file
   // file->Close();
}

