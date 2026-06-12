{
  TGraphErrors gr("file.dat");
    TF1 f("f","[0]*x+[1]",0,1);
    f.FixParameter(0.0);
    f.SetParameter(0,11616);

    gr.Draw("AP");
    gr.Fit("f");

}
