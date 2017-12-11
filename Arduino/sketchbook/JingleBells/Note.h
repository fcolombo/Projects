typedef struct s_notes {
  int frequency;
  int length;
  struct s_notes* next;
} notes;


notes* create_notes(int freq, int len) {
  notes* newNotes = (notes *) malloc(sizeof(notes));
  
  if (NULL != newNotes) {
    newNotes->frequency = freq;
    newNotes->length = len;
    newNotes->next = NULL;
  }
  
  return newNotes;
}

notes* delete_notes(notes* oldNotes) {

  if (NULL != oldNotes->next){
    delete_notes(oldNotes->next);
  }

  free(oldNotes);
}

notes* add_note(notes* song, int freq, int len)
{
  notes* newNotes = create_notes(freq, len);
  
  if (NULL != newNotes) {
    if (NULL != song->next) {
      add_note(song->next, freq, len);
    }
    else {
      song->next = newNotes;
    }
  }
        
  return song;
}
