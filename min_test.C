using namespace art;
using namespace std;

void min_test_simu(){

  //definition of InputTag
  string hittag = "gaushit";
  InputTag hit_tag(hittag);

  string trktag = "pandoraTrack";
  InputTag track_tag(trktag);

  string SpacePointtag = "pandora";
  InputTag spacep_tag(SpacePointtag);

  string caltag = "pandoraGnoCalo";
  InputTag calo_tag(caltag);

  string clustag = "pandora";
  InputTag cluster_tag(clustag);

  //replace "" by "yourfile.root"
  vector<string> filenames;
  filenames.push_back("");


  int i = 0;
  int k = 0;
  for(gallery::Event ev(filenames); !ev.atEnd(); ev.next()){

    if (i==k){//study for event n°k only

      auto const tracklist = ev.getValidHandle<vector<recob::Track>>(track_tag); //hitlist
      size_t ntracks = tracklist->size();

      auto const clusterlist = ev.getValidHandle<vector<recob::Cluster>>(cluster_tag); //hitlist
      size_t nclusters = clusterlist->size();

      auto const splist = ev.getValidHandle<vector<recob::SpacePoint>>(spacep_tag); //hitlist
      size_t nsps = splist->size();

      auto const hitlist = ev.getValidHandle<vector<recob::Hit>>(hit_tag); //hitlist
      size_t nhits = hitlist->size();

      cout<< "the event "<< i << " has "<< nhits << "  hits" << endl;
      cout<< "the event "<< i << " has "<< nsps << "  space-points" << endl;
      cout<< "the event "<< i << " has "<< nclusters << "  clusters" << endl;
      cout<< "the event "<< i << " has "<< ntracks << "  tracks" << endl;

      //creation of spacepoint/cluster/track association vector
      FindOne<recob::SpacePoint> Sp_Hit(hitlist, ev, spacep_tag);
      FindOne<recob::Cluster> Clu_Hit(hitlist, ev, cluster_tag);
      FindOne<recob::Track> Tra_Hit(hitlist, ev, track_tag);

      //counters
      int count_sp =0;
      int count_clu =0;
      int count_tra =0;

      for(size_t itk =0; itk<nhits; itk++){

        cet::maybe_ref<recob::SpacePoint const> sp_int(Sp_Hit.at(itk));
        cet::maybe_ref<recob::Cluster const> clu_int(Clu_Hit.at(itk));
        cet::maybe_ref<recob::Track const> tra_int(Tra_Hit.at(itk));

        if(sp_int.isValid())
          count_sp++;
        if(clu_int.isValid())
          count_clu++;
        if(tra_int.isValid())
         count_tra++;
      }

      cout << "On this "<< nhits<< " hits"<< endl;
      cout << " " << count_sp << " are associated with Valid Sp" << endl;
      cout << " " << count_clu << " are associated with Valid Clusters" << endl;
      cout << " " << count_tra << " are associated with Valid Tracks" << endl;
      cout << "################################################" << endl;
      cout << " "<< endl;

      count_sp =0;
      count_clu =0;
      count_tra =0;
      i++;
    }
  }
}
