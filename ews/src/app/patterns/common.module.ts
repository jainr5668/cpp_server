import { CommonModule } from '@angular/common';
import { HttpClient, HttpClientModule } from '@angular/common/http';
import { NgModule } from '@angular/core';
import { TranslateLoader, TranslateModule } from '@ngx-translate/core';
import { TranslateHttpLoader } from '@ngx-translate/http-loader';

const module = [TranslateModule, , HttpClientModule]


@NgModule({
  imports: [TranslateModule, HttpClientModule],
  exports: [TranslateModule, HttpClientModule],
})
export class SharedModule {}