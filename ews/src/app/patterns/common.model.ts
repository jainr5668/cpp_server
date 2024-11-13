export enum LinkTarget {
  BLANK = '_blank',
  SELF = '_self',
  PARENT = '_parent',
  TOP = '_top',
}

export enum LanguageList {
  ENGLISH = 'en',
  GERMAN = 'de',
  SPANISH = 'es',
  CHINESE = 'zh',
  FRENCH = 'fr',
  JAPNESE = 'ja',
}

export class clickListenerEvent {
  event: Event;
  id: string;
  data: any;
  constructor(event: Event, id?: string, data?: any) {
    this.event = event;
    this.id = id ?? null;
    this.data = data ?? null;
  }
}
