import { Component, OnInit, Input, Output, EventEmitter } from "@angular/core";
import { TranslateService } from "@ngx-translate/core";
import { ButtonModel, ButtonTypeEnum } from "@patterns/button";
import { clickListenerEvent } from "@patterns/common.model";
import { Observable } from "rxjs";
import { StringIdsType } from "src/stringIds";

@Component({
  selector: 'pattern-button',
  templateUrl: './button.component.html',
  styleUrls: ['./button.component.css'],
})
export class ButtonComponent implements OnInit {
  @Input() public button: ButtonModel;

  @Output() clickListener = new EventEmitter();

  class: string = '';
  colour: string = null;

  constructor(private translate: TranslateService) {
    // translate.setDefaultLang('en');
    // translate.use('en');
  }

  public getLocalizedString$(stringId: StringIdsType): Observable<string> {
    return this.translate.stream(stringId);
  }
  
  ngOnInit(): void {
    this.generateClass();
  }

  generateClass() {
    switch (this.button.buttonType) {
      case ButtonTypeEnum.PRIMARY:
        this.class = 'btn btn-outline-primary';
        break;
      case ButtonTypeEnum.SECONDRARY:
        this.class = 'btn btn-outline-secondary';
        break;
      case ButtonTypeEnum.DELETE:
        this.class = 'btn btn-outline-danger';
        break;
      case ButtonTypeEnum.WARNING:
        this.class = 'btn btn-outline-warning';
        break;
      default:
        console.error('type must be provided for the button to be generated');
    }
  }

  onClicked(event: Event) {
    const eventObject = new clickListenerEvent(event, this.button.id);
    if (this.button.event) {
      this.button.event(eventObject);
    } else {
      this.clickListener.emit(eventObject);
    }
  }
}
